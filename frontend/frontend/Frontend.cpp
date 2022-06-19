#include "Frontend.h"
#include "MageEngine.h"
using namespace Mage;

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

// Impl. for the frontend
Frontend::Frontend(const FrontendConfig& config) {
    gameRun = false;
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
        vm = wrenNewVM(&wrenConfig);
        MAGE_INFO("Frontend: Loaded the Wren VM!");
        // Store the project directory and run type
        uData.runType = config.itype;
        uData.projectDir = config.projectdir;
        // Now run the game
        runGame();
    }
}

std::string Frontend::getSource(const char* module) {
    if (uData.runType == CMD_RUN_CWD || uData.runType == CMD_RUN_DIR) {
        // If the project being run is a directory, navigate to and load the source file
        std::string path = uData.projectDir;
        path += "/Main.wren";
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

void Frontend::runGame() {
    interpretMain(); // First interpret main
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
        wrenFreeVM(vm);
    }
}