#ifndef MAGE_FRONTEND_H
    #define MAGE_FRONTEND_H
    // Enums to check the instruction type given to the MAGE application
    enum InstructType {
        CMD_NONE = 0,
        
        CMD_RUN_FUSED,
        CMD_RUN_DIR,
        CMD_RUN_CWD,
    };
    // Struct for configuring the frontend
    struct FrontendConfig {
        InstructType itype;
        const char* projectdir;
        void* userdata;

        FrontendConfig();
    };
#endif