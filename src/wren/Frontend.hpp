#ifndef MAGE_FRONTEND_HPP
    #define MAGE_FRONTEND_HPP
    #include <string>
    #include "wren/WrenAPI.hpp"

    namespace mage {
        // Struct for storing user data
        struct UserData {
            std::string projectDir;
            WrenLibrary* lib;
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
        };
    }
#endif