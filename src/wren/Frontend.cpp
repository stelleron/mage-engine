#include "wren/Frontend.hpp"
#include "utils/DebugTools.hpp"
#include <iostream>

namespace mage {
    // MAGE Engine modules
    const char* mageUtilsModule =
    "foreign class Vec2{\n"
    "   construct new(x,y){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "}\n"
    "foreign class Vec3{\n"
    "   construct new(x,y,z){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign z\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "   foreign z=(value)\n"
    "}\n"
    "foreign class Vec4{\n"
    "   construct new(x,y,z,w){}\n"
    "   foreign x\n"
    "   foreign y\n"
    "   foreign z\n"
    "   foreign w\n"
    "   foreign x=(value)\n"
    "   foreign y=(value)\n"
    "   foreign z=(value)\n"
    "   foreign w=(value)\n"
    "}\n"
    "foreign class Color{\n"
    "   construct new(r,g,b,a){}\n"
    "   static rgb(r,g,b){ Color.new(r,g,b,255) }\n"
    "   static rgba(r,g,b,a){ Color.new(r,g,b,a) }\n"
    "   static normal_rgb(r,g,b){ Color.new(r/255, g/255, b/255, 1.0) }\n"
    "   static normal_rgba(r,g,b,a){ Color.new(r/255, g/255, b/255, a/255) }\n"
    "   \n"
    "   foreign r\n"
    "   foreign g\n"
    "   foreign b\n"
    "   foreign a\n"
    "   foreign r=(value)\n"
    "   foreign g=(value)\n"
    "   foreign b=(value)\n"
    "   foreign a=(value)\n"
    "}\n";

    const char* mageRandomModule = 
    "class Random {\n"
    "   foreign static generate()\n"
    "   foreign static generate(min, max)\n"
    "   foreign static seed=(value)\n"
    "}\n"
    ;

    const char* mageAppModule = 
    "import \"mage-utils\" for Vec2, Color\n"
    "class AppConfig {\n"
    "   construct new() {}\n"
    "   foreign width=(value)\n"
    "   foreign height=(value)\n"
    "   foreign title=(value)\n"
    "   foreign background_color=(value)\n"
    "   foreign resizable=(value)\n"
    "   foreign fullscreen=(value)\n"
    "   foreign decorated=(value)\n"
    "   foreign maximized=(value)\n"
    "   foreign vsync=(value)\n"
    "   foreign transparent=(value)\n"
    "   foreign focused=(value)\n"
    "   foreign halt_while_hidden=(value)\n"
    "   foreign fps_cap=(value)\n"
    "   foreign opacity=(value)\n"
    "   foreign min_size=(value)\n"
    "   foreign max_size=(value)\n"
    "}\n"
    "class GameContext {\n"
    "   construct new() {}\n"
    "}\n"
    "class RenderContext {\n"
    "   construct new() {}\n"
    "}\n"
    ;
    

    // === MAGE FUNCTION DEFINITIONS
    // == AppConfig
    void appConfigSetWindowWidth(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->width = GET_INT(1);
    }

    void appConfigSetWindowHeight(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->height = GET_INT(1);
    }

    void appConfigSetWindowTitle(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->title = GET_STR(1);
    }

    void appConfigSetWindowResizable(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->resizable = GET_BOOL(1);
    }

    void appConfigSetWindowFullscreen(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->fullscreen = GET_BOOL(1);
    }

    void appConfigSetWindowDecorated(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->decorated = GET_BOOL(1);
    }

    void appConfigSetWindowMaximized(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->maximized = GET_BOOL(1);
    }

    void appConfigSetWindowVSync(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->vsync = GET_BOOL(1);
    }

    void appConfigSetWindowTransparent(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->transparent = GET_BOOL(1);
    }

    void appConfigSetWindowFocused(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->focused = GET_BOOL(1);
    }

    void appConfigSetWindowHaltWhileHidden(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->halt_while_hidden = GET_BOOL(1);
    }

    void appConfigSetWindowFPSCap(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->fps_cap = GET_INT(1);
    }

    void appConfigSetWindowOpacity(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->resizable = GET_FLOAT(1);
    }

    void appConfigSetWindowMinSize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->min_size = *(arcana::Vector2*)GET_FOREIGN(1);
    }

    void appConfigSetWindowMaxSize(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->max_size = *(arcana::Vector2*)GET_FOREIGN(1);
    }

    void appConfigSetWindowBackgroundColor(WrenVM* vm) {
        UserData* uData = (UserData*)GET_USER_DATA();
        uData->config->background_color = *(arcana::Color*)GET_FOREIGN(1);
    }
    //== Vector2
    void vec2Constructor(WrenVM* vm) {
        arcana::Vector2* vec = SET_FOREIGN(arcana::Vector2);
        new (vec) arcana::Vector2(GET_FLOAT(1), GET_FLOAT(2));
    }

    void vec2GetX(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec2GetY(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec2SetX(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec2SetY(WrenVM* vm) {
        arcana::Vector2* vec = (arcana::Vector2*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }
    //== Vector3
    void vec3Constructor(WrenVM* vm) {
        arcana::Vector3* vec = SET_FOREIGN(arcana::Vector3);
        new (vec) arcana::Vector3(GET_FLOAT(1), GET_FLOAT(2), GET_FLOAT(3));
    }

    void vec3GetX(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec3GetY(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec3GetZ(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        SET_NUM(vec->z, 0);
    }

    void vec3SetX(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec3SetY(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }

    void vec3SetZ(WrenVM* vm) {
        arcana::Vector3* vec = (arcana::Vector3*)GET_FOREIGN(0);
        vec->z = GET_FLOAT(1);
    }
    //== Vector4
    void vec4Constructor(WrenVM* vm) {
        arcana::Vector4* vec = SET_FOREIGN(arcana::Vector4);
        new (vec) arcana::Vector4(GET_FLOAT(1), GET_FLOAT(2), GET_FLOAT(3), GET_FLOAT(4));
    }

    void vec4GetX(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->x, 0);
    }

    void vec4GetY(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->y, 0);
    }

    void vec4GetZ(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->z, 0);
    }

    void vec4GetW(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        SET_NUM(vec->w, 0);
    }

    void vec4SetX(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->x = GET_FLOAT(1);
    }

    void vec4SetY(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->y = GET_FLOAT(1);
    }

    void vec4SetZ(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->z = GET_FLOAT(1);
    }

    void vec4SetW(WrenVM* vm) {
        arcana::Vector4* vec = (arcana::Vector4*)GET_FOREIGN(0);
        vec->w = GET_FLOAT(1);
    }
    //== Color
    void colorConstructor(WrenVM* vm) {
        arcana::Color* color = SET_FOREIGN(arcana::Color);
        new (color) arcana::Color(GET_INT(1), GET_INT(2), GET_INT(3), GET_INT(4));
    }

    void colorGetR(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->r, 0);
    }

    void colorGetG(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->g, 0);
    }

    void colorGetB(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->b, 0);
    }

    void colorGetA(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        SET_NUM(color->a, 0);
    }

    void colorSetR(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->r = GET_INT(1);
        }
    }

    void colorSetG(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->g = GET_INT(1);
        }
    }

    void colorSetB(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->b = GET_INT(1);
        }
    }

    void colorSetA(WrenVM* vm) {
        arcana::Color* color = (arcana::Color*)GET_FOREIGN(0);
        int num = GET_INT(1);
        if (num > 255 && num < 0) {
            ERROR("Error: Color value set is not within bounds!")
        }
        else {
            color->a = GET_INT(1);
        }
    }

    //== Random
    void randomGenerate(WrenVM* vm) {
        SET_NUM(arcana::random::generate(),0);
    } 
    void randomGenerateNum(WrenVM* vm) {
        SET_NUM(arcana::random::generateNum(GET_INT(1), GET_INT(2)),0);
    }
    void randomSetSeed(WrenVM* vm) {
        arcana::random::setSeed(GET_INT(1));
    } 

    // === END MAGE FUNCTION DEFINITIONS

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
        else if (strcmp(module, "mage-utils") == 0) {
            return mageUtilsModule;
        }
        else if (strcmp(module, "mage-random") == 0) {
            return mageRandomModule;
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
        .declModule("mage-utils")
            .declClass("Vec2")
                .declForeignAlloc(vec2Constructor)
                .declForeignFn("x", false, vec2GetX)
                .declForeignFn("y", false, vec2GetY)
                .declForeignFn("x=(_)", false, vec2SetX)
                .declForeignFn("y=(_)", false, vec2SetY)
            .declClass("Vec3")
                .declForeignAlloc(vec3Constructor)
                .declForeignFn("x", false, vec3GetX)
                .declForeignFn("y", false, vec3GetY)
                .declForeignFn("z", false, vec3GetZ)
                .declForeignFn("x=(_)", false, vec3SetX)
                .declForeignFn("y=(_)", false, vec3SetY)
                .declForeignFn("z=(_)", false, vec3SetZ)
            .declClass("Vec4")
                .declForeignAlloc(vec4Constructor)
                .declForeignFn("x", false, vec4GetX)
                .declForeignFn("y", false, vec4GetY)
                .declForeignFn("z", false, vec4GetZ)
                .declForeignFn("w", false, vec4GetW)
                .declForeignFn("x=(_)", false, vec4SetX)
                .declForeignFn("y=(_)", false, vec4SetY)
                .declForeignFn("z=(_)", false, vec4SetZ)
                .declForeignFn("w=(_)", false, vec4SetW)
            .declClass("Color")
                .declForeignAlloc(colorConstructor)
                .declForeignFn("r", false, colorGetR)
                .declForeignFn("g", false, colorGetG)
                .declForeignFn("b", false, colorGetB)
                .declForeignFn("a", false, colorGetA)
                .declForeignFn("r=(_)", false, colorSetR)
                .declForeignFn("g=(_)", false, colorSetG)
                .declForeignFn("b=(_)", false, colorSetB)
                .declForeignFn("a=(_)", false, colorSetA)
        .declModule("mage-random")
            .declClass("Random")
                .declForeignFn("generate()", true, randomGenerate)
                .declForeignFn("generate(_,_)", true, randomGenerateNum)
                .declForeignFn("seed=(_)", true, randomSetSeed)
        .declModule("mage-app")
            .declClass("AppConfig")
                .declForeignFn("width=(_)", false, appConfigSetWindowWidth)
                .declForeignFn("height=(_)", false, appConfigSetWindowHeight)
                .declForeignFn("title=(_)", false, appConfigSetWindowTitle)
                .declForeignFn("background_color=(_)", false, appConfigSetWindowBackgroundColor)
                .declForeignFn("resizable=(_)", false, appConfigSetWindowResizable)
                .declForeignFn("fullscreen=(_)", false, appConfigSetWindowFullscreen)
                .declForeignFn("decorated=(_)", false, appConfigSetWindowDecorated)
                .declForeignFn("maximized=(_)", false, appConfigSetWindowMaximized)
                .declForeignFn("vsync=(_)", false, appConfigSetWindowVSync)
                .declForeignFn("transparent=(_)", false, appConfigSetWindowTransparent)
                .declForeignFn("focused=(_)", false, appConfigSetWindowFocused)
                .declForeignFn("halt_while_hidden=(_)", false, appConfigSetWindowHaltWhileHidden)
                .declForeignFn("fps_cap=(_)", false, appConfigSetWindowFPSCap)
                .declForeignFn("opacity=(_)", false, appConfigSetWindowOpacity)
                .declForeignFn("min_size=(_)", false, appConfigSetWindowMinSize)
                .declForeignFn("max_size=(_)", false, appConfigSetWindowMaxSize)
        ;
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