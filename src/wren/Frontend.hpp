#ifndef MAGE_FRONTEND_HPP
    #define MAGE_FRONTEND_HPP
    #include <string>
    #include "Arcana2D.hpp"
    #include "wren/WrenAPI.hpp"

    namespace mage {
        // Struct for storing user data
        struct UserData {
            std::string projectDir;
            WrenLibrary* lib;

            arcana::AppConfig* config;
            arcana::GameContext* game_ctx;
            arcana::RenderContext* render_ctx;
        };

        // Struct to interface with the frontend
        struct Frontend { 
            // Stores the wren handles for the MAGE application
            struct MageApplication {
                WrenHandle* mainInstance;
                WrenHandle* configFunc;
                WrenHandle* initFunc;
                WrenHandle* updateFunc;
                WrenHandle* renderFunc;
                WrenHandle* finishFunc;

                WrenHandle* configInstance;
                WrenHandle* gameCtxInstance;
                WrenHandle* renderCtxInstance;
            };
            // Wren data
            WrenVM* vm;
            WrenConfiguration wrenConfig;
            // User data
            UserData uData;
            MageApplication app;
            WrenLibrary mageLib;
            public:
                Frontend();
                ~Frontend();

                void declMageLib();
                void releaseFunctionHandles();
                void start(const std::string& fpath);
                void loadMain();
        };
    }
#endif