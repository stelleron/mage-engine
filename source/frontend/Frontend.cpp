#include "frontend/Frontend.hpp"
#include "utils/DebugTools.hpp"
#include "utils/FileSys.hpp"

namespace Mage {
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
        WrenLibrary* lib = uData->lib;
        return lib->searchFn(module, className, isStatic, signature);
    }

    // Used to bind foreign classes
    WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className) 
    {
        UserData* uData = (UserData*)GET_USER_DATA();
        WrenLibrary* lib = uData->lib;
        WrenForeignClassMethods fClass;
        lib->searchFClass(module, className, &fClass);
        return fClass;
    }
    // Used to get the file source for MAGE modules
    const char* getMageModuleSource(const char* module) {
        if (strcmp(module, "mage-app") == 0) {
            return "";
        }
        else {
            return "";
        }
    }

    // Just get the source 
    std::string getSource(const char* module, RunType rType, std::string& path, Datapak* pak) {
        switch(rType) {
            case RUN_PROJECT: {
                    std::string modPath = path + module; 
                    return loadFile(modPath); 
                }
                break;
            case RUN_PACKAGE: {
                    return pak->read(module);
                }  
                break;
            default: return "";
        }
    }

    // Get the module source
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

    void Frontend::declMageLib() {
        MAGE_INFO("Wren: Declared the MAGE library!");
    }

    // Impl. for the Frontend
    Frontend::Frontend(const std::string& fpath, RunType rType) {
        // First initialise the frontend variables
        closeGame = false;
        // If the run type is a package, load it
        if (rType == RUN_PACKAGE) {
            uData.mageproject = MAGE_ALLOC(Datapak);
            uData.mageproject->load(fpath.c_str());
        }
        // Now load up every part of the MAGE engine
        // First the VM
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
        // Set user data
        uData.projectDir = (char*)fpath.c_str();
        uData.rType = rType;
        SET_USER_DATA(&uData);
        // Now run the game
        runGame();
    }

    void Frontend::runGame() {
        interpretMain(); // First interpret main.wren
        loadMainClass(); // Then load the Wren handles of the Main class
        loadFunctionHandles(); // Then get all the visible functions attached to it
        runGameLoop(); // Finally run the game loop endlessly
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
        // To use later for function attributes
        /*
        WrenHandle* attribFunc = MAKE_HANDLE("attributes");
        WrenHandle* methodAttribFunc = MAKE_HANDLE("methods");
        GET_VARIABLE("main", "Main", 0);
        CALL_FUNC(attribFunc);
        if (GET_SLOT_TYPE(0) != WREN_TYPE_NULL) {
            CALL_FUNC(methodAttribFunc);
        }
        RELEASE_HANDLE(attribFunc);
        RELEASE_HANDLE(methodAttribFunc);
        */
        // Now time to get the update, render and finish functions
    // Now time to get the update, render and finish functions
        app.updateFunc = MAKE_HANDLE("update(_)");
        app.renderFunc = MAKE_HANDLE("render()");
        app.finishFunc = MAKE_HANDLE("finish()");
    }

    void Frontend::interpretMain() {
        std::string source = getSource("main.wren", uData.rType, uData.projectDir, uData.mageproject);
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

    void Frontend::runGameLoop() {
        ENSURE_SLOTS(2);
        while (!closeGame) {
            // Update func
            ENSURE_SLOTS(2);
            SET_HANDLE(app.mainInstance, 0);
            SET_NUM(60, 1);
            CALL_FUNC(app.updateFunc);
            // Render func
            ENSURE_SLOTS(1);
            SET_HANDLE(app.mainInstance, 0);
            CALL_FUNC(app.renderFunc);
            // NOTE: Debug only!
            closeGame = true;
        }
        // Finish func
        SET_HANDLE(app.mainInstance, 0);
        CALL_FUNC(app.finishFunc);
    }


    void Frontend::releaseFunctionHandles() {
        RELEASE_HANDLE(app.mainInstance);
        RELEASE_HANDLE(app.updateFunc);
        RELEASE_HANDLE(app.renderFunc);
        RELEASE_HANDLE(app.finishFunc);
    }

    Frontend::~Frontend() {
        MAGE_INFO("Frontend: Destroying the engine!");
        // Release handles and Wren VM
        releaseFunctionHandles();
        wrenFreeVM(vm);
    }
}