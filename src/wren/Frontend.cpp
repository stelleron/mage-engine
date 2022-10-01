#include "wren/Frontend.hpp"
#include "utils/DebugTools.hpp"
#include "Arcana2D.hpp"
#include <iostream>

namespace mage {
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

    Frontend::Frontend() {

    }

    void Frontend::start(const std::string& fpath) {
        // Now load up every part of the MAGE engine
        // First the VM
        wrenInitConfiguration(&wrenConfig);
            wrenConfig.writeFn = writeFn;
            wrenConfig.errorFn = errorFn;
        vm = wrenNewVM(&wrenConfig);
        MAGE_INFO("Frontend: Loaded the Wren VM!");
        // Now declare the MAGE library 
        declMageLib();
        // Set user data
        uData.projectDir = fpath;
        uData.lib = &mageLib;
        SET_USER_DATA(&uData);
        // Now load the main class
    }

    void Frontend::declMageLib() {
        MAGE_INFO("Wren: Declared the MAGE library!");
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