#ifndef MAGE_FRONTEND_HPP
    #define MAGE_FRONTEND_HPP
    #include <string>
    #include "datapak.hpp"
    #include "frontend/WrenAPI.hpp"

    namespace Mage {
        // Enum to check the run variation
        enum RunType {
            RUN_PROJECT, // Run a project
            RUN_PACKAGE, // Run a .mageproj
            RUN_STORED, // Run the stored project(Dist mode only)
            RUN_UNKNOWN, // Unknown run type, meant to return an error
        };
        // Struct for storing user data
        struct UserData {
            std::string projectDir;
            RunType rType;

            WrenLibrary* lib;
            Datapak* mageproject;
        };
        // Class to interface with the frontend
        class Frontend { 
            // Stores the wren handles for the MAGE application
            struct MageApplication {
                WrenHandle* mainInstance;

                WrenHandle* updateFunc;
                WrenHandle* renderFunc;
                WrenHandle* finishFunc;
            };
            bool closeGame; // Should the game be closed?
            // Wren data
            WrenVM* vm;
            WrenConfiguration wrenConfig;
            // User data
            UserData uData;
            MageApplication app;
            WrenLibrary mageLib;
            public:
                Frontend(const std::string& fpath, RunType rType);
                ~Frontend();

                void interpretMain();
                void declMageLib();
                void runGame();

                void loadMainClass();
                void loadFunctionHandles();
                void releaseFunctionHandles();
                void runGameLoop();

        };
    }
#endif