#ifndef MAGE_FRONTEND_H
    #define MAGE_FRONTEND_H
    #include "wren.hpp"
    // Enums to check the instruction type given to the MAGE application
    enum InstructType {
        CMD_NONE = 0,

        CMD_HELP,
        
        CMD_RUN_FUSED, // Run the fused .mageproj stored in the MAGE engine
        CMD_RUN_DIR, // Run the project at the given directory
        CMD_RUN_CWD, // Run the project in the current directory
    };
    // Struct for configuring the frontend
    struct FrontendConfig {
        InstructType itype;
        const char* projectdir;

        FrontendConfig();
    };
    // Class to interface with the frontend
    class Frontend { 
        // Should the game be run?
        bool gameRun; 
        // Wren data
        WrenVM* vm;
        WrenConfiguration wrenConfig;
        // Wren handles for the application
        WrenHandle* appInstance;
        WrenHandle* initFunc;
        WrenHandle* updateFunc;
        WrenHandle* renderFunc;
        public:
            Frontend(const FrontendConfig& config);
            ~Frontend();

            void runGame();
    };
#endif