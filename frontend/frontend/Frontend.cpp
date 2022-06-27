#include "Frontend.h"
#include "MageEngine.h"
using namespace Mage;
// Wren modules
#include "modules/MageApp.h"

// Impl. for the frontend config
FrontendConfig::FrontendConfig() {

}

// Impl. for the VM
// Print function for the Wren VM
void writeFn(WrenVM* vm, const char* str) {
    std::printf("%s", str);
}

// Error reporting function
void errorFn(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg) {
    switch (errorType) 
    {
        case WREN_ERROR_COMPILE:
        {
            MAGE_ERROR("[{0} line {1}] [Error] {2}", module, line, msg);
        } break;

        case WREN_ERROR_STACK_TRACE:
        {
            MAGE_ERROR("[{0} line {1}] in {2}", module, line, msg);
        } break;

        case WREN_ERROR_RUNTIME:
        {
            MAGE_ERROR("[Runtime Error] {0}", msg);
        } break;
    }
}

// Used to bind foreign functions
WrenForeignMethodFn bindForeignFn(WrenVM* vm, const char* module, const char* className,
                             bool isStatic, const char* signature) 
{
    UserData* uData = (UserData*)GET_USER_DATA();
    MageLibrary* lib = uData->lib;
    return lib->searchFn(module, className, isStatic, signature);
}

// Used to bind foreign classes
WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className) 
{
    UserData* uData = (UserData*)GET_USER_DATA();
    MageLibrary* lib = uData->lib;
    WrenForeignClassMethods fClass;
    lib->searchFClass(module, className, &fClass);
    return fClass;
}

// Used to get the file source for MAGE modules
const char* getMageModuleSource(const char* module) {
    if (strcmp(module, MAGE_APP) == 0) {
        return mageAppModule;
    }
    else {
        return "";
    }
}

// Get the file source
const char* getSourceForModule(WrenVM* vm, const char* name) {
    
    // First check if the module is part of the mage modules
    const char* modSource = getMageModuleSource(name);
    if (strcmp(modSource, "") != 0) {
        return modSource;
    }
    // Loading a file module
    return "";
}

// Wren function for loading files
WrenLoadModuleResult loadModuleFn(WrenVM* vm, const char* name) {
    WrenLoadModuleResult result = {0};
        result.source = getSourceForModule(vm, name);
    return result;
}

// Impl. for the frontend
Frontend::Frontend(const FrontendConfig& config) {
    gameRun = false;
    gameClose = false;
    // Check the run command to see what to do
    switch (config.itype) {
        case CMD_NONE: break;
        case CMD_HELP: 
            MAGE_INFO("MAGE is a 2D game engine that uses the Wren scripting language to Make Awesome Games Easy!");
            break;
        case CMD_RUN_FUSED... CMD_RUN_CWD:  
            gameRun = true; 
            break;
        default: break;
    }

    // If the game is being run, create the Wren VM
    if (gameRun) {
        wrenInitConfiguration(&wrenConfig);
            wrenConfig.writeFn = writeFn;
            wrenConfig.errorFn = errorFn;
            wrenConfig.loadModuleFn = loadModuleFn;
            wrenConfig.bindForeignMethodFn = bindForeignFn;
            wrenConfig.bindForeignClassFn = bindForeignClass;

        vm = wrenNewVM(&wrenConfig);
        MAGE_INFO("Frontend: Loaded the Wren VM!");
        // Now declare the MAGE library 
        declMageLib();
        // Store the project directory and run type
        uData.runType = config.itype;
        uData.projectDir = config.projectdir;
        uData.lib = &mageLib;
        SET_USER_DATA(&uData);
        // Now run the game
        runGame();
    }
}

std::string Frontend::getSource(const char* module) {
    if (uData.runType == CMD_RUN_CWD || uData.runType == CMD_RUN_DIR) {
        // If the project being run is a directory, navigate to and load the source file
        std::string path = uData.projectDir;
        path += "/main.wren";
        return loadFile(path);
    }
    else if (uData.runType == CMD_RUN_FUSED || uData.runType == CMD_RUN_CWD_PACKAGE 
            || uData.runType == CMD_RUN_DIR_PACKAGE) {
        // If the project has been packaged, get the module source from the .mageproj file
        return "System.print(45)";
    }
    else {
        return "None";
    }
}

void Frontend::declMageLib() {
    mageLib.declModule(MAGE_APP)
        .declClass("MageConfig")
            .declForeignAlloc(mageCreateMageConfig)
        .declClass("NativeApp")
            .declForeignAlloc(mageCreateMageApp)
            .declForeignFinalise(mageDestroyMageApp);
    MAGE_INFO("Wren: Declared the MAGE library!");
}

void Frontend::loadMainClass() {
    // Load the main class
    ENSURE_SLOTS(1);
    GET_VARIABLE("main", "Main", 0);
    WrenHandle* constructor = MAKE_HANDLE("new()");
    CALL_FUNC(constructor);
    RELEASE_HANDLE(constructor);
    app.mainInstance = GET_HANDLE(0);
}

void Frontend::loadFunctionHandles() {
    WrenHandle* attribFunc = MAKE_HANDLE("attributes");
    WrenHandle* methodAttribFunc = MAKE_HANDLE("methods");
    GET_VARIABLE("main", "Main", 0);
    CALL_FUNC(attribFunc);
    if (GET_SLOT_TYPE(0) != WREN_TYPE_NULL) {
        CALL_FUNC(methodAttribFunc);
    }
    RELEASE_HANDLE(attribFunc);
    RELEASE_HANDLE(methodAttribFunc);
    // Now time to get the update, render and finish functions
    app.updateFunc = MAKE_HANDLE("update(_)");
    app.renderFunc = MAKE_HANDLE("render()");
    app.finishFunc = MAKE_HANDLE("finish()");
}

void Frontend::releaseFunctionHandles() {
    RELEASE_HANDLE(app.mainInstance);
    RELEASE_HANDLE(app.updateFunc);
    RELEASE_HANDLE(app.renderFunc);
    RELEASE_HANDLE(app.finishFunc);
}

void Frontend::runGameLoop() {
    ENSURE_SLOTS(2);
    while (!gameClose) {
        // Update func
        ENSURE_SLOTS(2);
        SET_HANDLE(app.mainInstance, 0);
        SET_NUM(60, 1);
        CALL_FUNC(app.updateFunc);
        gameClose = GET_BOOL(0);
        // Render func
        ENSURE_SLOTS(1);
        SET_HANDLE(app.mainInstance, 0);
        CALL_FUNC(app.renderFunc);
    }
    // Finish func
    SET_HANDLE(app.mainInstance, 0);
    CALL_FUNC(app.finishFunc);
}

void Frontend::runGame() {
    interpretMain(); // First interpret main.wren
    loadMainClass(); // Then load the Wren handles of the Main class
    loadFunctionHandles(); // Then get all the visible functions attached to it
    runGameLoop(); // Finally run the game loop endlessly
}


void Frontend::interpretMain() {
    std::string source = getSource("main");
    WrenInterpretResult result = wrenInterpret(vm, "main", source.c_str()); 
    // Then handle the results of the interpretation
    switch (result) {
    case WREN_RESULT_COMPILE_ERROR:
      { MAGE_ERROR("Wren: Encountered a compile error while running the project!"); } break;
    case WREN_RESULT_RUNTIME_ERROR:
      { MAGE_ERROR("Wren: Encountered a runtime error while running the project!"); } break;
    case WREN_RESULT_SUCCESS:
      { MAGE_INFO("Wren: Succesfully compiled main!"); } break;
    }
}

Frontend::~Frontend() {
    // Free the Wren VM
    if (gameRun) {
        MAGE_INFO("Frontend: Freeing the Wren VM!");
        releaseFunctionHandles(); // Release the function handles
        wrenFreeVM(vm);
    }
}