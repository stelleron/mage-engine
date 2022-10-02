#include "wren/Frontend.hpp"
#include "utils/DebugTools.hpp"
#include <iostream>

namespace mage {
    // MAGE Engine modules
    const char* mageAppModule = 
    "class AppConfig {\n"
    "   construct new() {}\n"
    "   foreign width=(value)\n"
    "}\n"
    "class GameContext {\n"
    "   construct new() {}\n"
    "}\n"
    "class RenderContext {\n"
    "   construct new() {}\n"
    "}\n";
    

    // MAGE Engine functions
    void appConfigSetWindowWidth(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->width = GET_INT(1);
    }

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

    // Used to get the file source for MAGE modules
    const char* getMageModuleSource(const char* module) {
        if (strcmp(module, "mage-app") == 0) {
            return mageAppModule;
        }
        else {
            return "";
        }
    }

    // Get the module source
    const char* getSourceForModule(WrenVM* vm, const char* name) {
        // First check if the module is part of the mage modules
        const char* modSource = getMageModuleSource(name);
        if (strcmp(modSource, "") != 0) {
            return modSource;
        }
        else {
            UserData* data = (UserData*)GET_USER_DATA()
            std::string path = data->projectDir;
            path += name;
            path += ".wren";
            size_t fsize;
            return arcana::filesystem::loadFileText(path, fsize);
        }
    }
    
    // Wren function for loading files
    WrenLoadModuleResult loadModuleFn(WrenVM* vm, const char* name) {
        WrenLoadModuleResult result = {0};
            result.source = getSourceForModule(vm, name);
        return result;
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

    Frontend::Frontend() {

    }

    void Frontend::start(const std::string& fpath) {
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
        uData.projectDir = fpath;
        uData.lib = &mageLib;
        SET_USER_DATA(&uData);
        // Now load the main class
        loadMain();
    }

    void Frontend::loadMain() {
        std::string source = getSourceForModule(vm, "main");
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
        // Now load the main class and function handles
        // Load the main class
        ENSURE_SLOTS(1);
        GET_VARIABLE("main", "Main", 0);
        WrenHandle* constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.mainInstance = GET_HANDLE(0);
        // Now time to get all attached functions
        app.configFunc = MAKE_HANDLE("config(_)");
        app.initFunc = MAKE_HANDLE("init(_)");
        app.updateFunc = MAKE_HANDLE("update(_)");
        app.renderFunc = MAKE_HANDLE("render(_)");
        app.finishFunc = MAKE_HANDLE("finish()");

        // And also load the context and config classes
        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "AppConfig", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.configInstance = GET_HANDLE(0);

        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "GameContext", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.gameCtxInstance = GET_HANDLE(0);

        ENSURE_SLOTS(1);
        GET_VARIABLE("mage-app", "RenderContext", 0);
        constructor = MAKE_HANDLE("new()");
        CALL_FUNC(constructor);
        RELEASE_HANDLE(constructor);
        app.renderCtxInstance = GET_HANDLE(0);
    }

    void Frontend::declMageLib() {
        mageLib
        .declModule("mage-app")
            .declClass("AppConfig")
                .declForeignFn("width=(_)", false, appConfigSetWindowWidth);
        MAGE_INFO("Wren: Declared the MAGE library!");
    }

    void Frontend::releaseFunctionHandles() {
        RELEASE_HANDLE(app.mainInstance);
        RELEASE_HANDLE(app.configFunc);
        RELEASE_HANDLE(app.initFunc);
        RELEASE_HANDLE(app.updateFunc);
        RELEASE_HANDLE(app.renderFunc);
        RELEASE_HANDLE(app.finishFunc);
        RELEASE_HANDLE(app.configInstance);
        RELEASE_HANDLE(app.gameCtxInstance);
        RELEASE_HANDLE(app.renderCtxInstance);
    }

    Frontend::~Frontend() {
        MAGE_INFO("Frontend: Destroying the engine!");
        // Release handles and Wren VM
        releaseFunctionHandles();
        wrenFreeVM(vm);
    }
}