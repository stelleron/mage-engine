#ifndef MAGE_FILESYS_HPP
    #define MAGE_FILESYS_HPP
    #include "whereami.h"
    namespace Mage {
        // Enum to store path types
        enum PathType {
            FILE_PATH = 0,
            DIR_PATH,
            UNKNOWN_PATH,
        };

        // Check if a given path leads to a file or a directory 
        PathType getPathType(const char* path);
        // Gets the path of the current executable
        std::string getExecPath();
        // Gets the parent directory of the current exec., going back by a specified number
        std::string rewindPath(const std::string& path, int val);
        // Grab a filename/folder path from the end of a specified path
        std::string getPathEnd(const std::string& path);
        // Load a file and get it's content 
        const char* loadFile(std::string& path); 
        const char* loadFile(const char* path);
        // Unload the file's data
        void unloadFile(const char* source);
        // Add a slash to the end of the file path if needed
        void addSlash(std::string& path);
        // Get the extension of a file
        std::string getFileExtension(const std::string& filepath);
        // Remove a portion of a given file path
        std::string removePartOfFilePath(const std::string& src, const std::string& remove_str);
        // Struct to store file data
        struct File {
            char* source;
            File(const char* path);
            ~File();
        };
    }
#endif