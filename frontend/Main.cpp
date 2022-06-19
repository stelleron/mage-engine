#include <string.h>
#include <filesystem>

#include "MageEngine.h"
#include "frontend/Frontend.h"

using namespace Mage;

InstructType handleArgs(int count, char** arguments, std::string* path) {
    // If there is only 1 argument, run the stored application
    if (count == 1) {
        MAGE_INFO("Mage: Running the stored application!");
        return CMD_RUN_FUSED;
    }
    // If there is a second argument provided, check what it is
    else if (count == 2) {
        if (strcmp(arguments[1] , "run") == 0) {
            MAGE_INFO("Mage: Running project in the current directory...");
            *path = std::filesystem::current_path();
            return CMD_RUN_CWD;
        }
        if (strcmp(arguments[1], "help") == 0) {
            return CMD_HELP;
        }
    }
    // If there are three arguments, check what they are
    else if (count == 3) {
        if (strcmp(arguments[1] , "run") == 0) {
            MAGE_INFO("Mage: Running a project with a given directory...");
            *path = arguments[2];
            MAGE_INFO("Directory given: {0}", *path);
            return CMD_RUN_DIR;
        } 
    }
    // Otherwise, return an error
    else {
        MAGE_INFO("Error: Too many arguments provided!");
        return CMD_NONE;
    }
}

int main(int argc, char** argv) {
    // Initialise the debugger
    DebugTools::Init();
    // Handle the given arguments
    std::string projectDir = "None Given or Used";
    InstructType iType = handleArgs(argc, argv, &projectDir);
    // If CMD_NONE was returned, exit the app
    if (iType == CMD_NONE) {
        return 0;
    }
    // Create the frontend config
    FrontendConfig config;
        config.itype = iType;
        config.projectdir = projectDir.c_str();
    // Initialise the frontend
    Frontend frontend(config);
}