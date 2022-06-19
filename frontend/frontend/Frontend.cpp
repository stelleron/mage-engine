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
        // Load the config.toml annd configure the game engine
        std::string configDir = config.projectdir;
        configDir += "/config.toml";
    }
}

void Frontend::runGame() {

}

Frontend::~Frontend() {
    // Free the Wren VM
    if (gameRun) {
        MAGE_INFO("Frontend: Freeing the Wren VM!");
        wrenFreeVM(vm);
    }
}