#ifndef MAGE_FILESYSTEM_H
    #define MAGE_FILESYSTEM_H
    #include "whereami.h"
    namespace Mage {
        // Gets the path of the current executable
        std::string getExecPath();
        // Gets the path of the MAGE module
        std::string getModulePath();
        // Gets the parent directory of the current exec., going back by a specified number
        std::string rewindPath(int val);
        // Rewinds a given path by a specific number 
        std::string rewindPath(std::string& path, int val);
        // Load a file and get it's content 
        const char* loadFile(std::string& path); 
        const char* loadFile(const char* path);
        // Unload the file's data
        void unloadFile(const char* source);
        // Struct to store file data
        struct File {
            char* source;
            File(const char* path);
            ~File();
        };
    }
#endif