#ifndef MAGE_FRONTEND_H
    #define MAGE_FRONTEND_H
    #include "WrenMacros.h"
    #include "MageAPI.h"
    #include <string>
    #define ENUM_NAME(arg) #arg
    typedef WrenLibrary MageLibrary;
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
        std::string projectDir;
        MageLibrary* lib;
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
        bool gameRun; // Should the game be run?
        bool gameClose; // Should the game be closed?
        // Wren data
        WrenVM* vm;
        WrenConfiguration wrenConfig;
        // User data
        UserData uData;
        MageApplication app;
        MageLibrary mageLib;

        public:
            Frontend(const FrontendConfig& config);
            ~Frontend();

            std::string getSource(const char* module);

            void interpretMain();
            void declMageLib();
            void runGame();

            void loadMainClass();
            void loadFunctionHandles();
            void releaseFunctionHandles();
            void runGameLoop();

    };
#endif