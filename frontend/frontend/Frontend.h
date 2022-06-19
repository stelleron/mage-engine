#ifndef MAGE_FRONTEND_H
    #define MAGE_FRONTEND_H
    #include "wren.hpp"
    #include <string>
    #define ENUM_NAME(arg) #arg
    // Enums to check the instruction type given to the MAGE application
    enum InstructType {
        CMD_NONE = 0,

        CMD_HELP,
        
        CMD_RUN_FUSED, // Run the fused .mageproj stored in the MAGE engine
        CMD_RUN_DIR, // Run the project at the given directory
        CMD_RUN_CWD, // Run the project in the current directory
        CMD_RUN_DIR_PACKAGE, // Run the .mageproj stored at the given directory 
        CMD_RUN_CWD_PACKAGE,
    };
    // Struct for configuring the frontend
    struct FrontendConfig {
        InstructType itype;
        std::string projectdir;

        FrontendConfig();
    };
    // Struct for storing user data
    struct UserData {
        InstructType runType;
    };
    // Class to interface with the frontend
    class Frontend { 
        bool gameRun; // Should the game be run?
        // Wren data
        WrenVM* vm;
        WrenConfiguration wrenConfig;
        // User data
        UserData uData;
        // Wren handles for the application
        WrenHandle* appInstance;
        WrenHandle* initFunc;
        WrenHandle* updateFunc;
        WrenHandle* renderFunc;
        public:
            Frontend(const FrontendConfig& config);
            ~Frontend();

            std::string getSource(const char* module);
            void interpretMain();
            void runGame();
    };
#endif