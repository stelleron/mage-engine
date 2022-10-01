#ifndef ARCANA2D_FILESYSTEM
    #define ARCANA2D_FILESYSTEM
    #include <string>
    namespace arcana {
        // Filesystem namespace
        namespace filesystem {
            // Set the working directory
            void setDir(const std::string& dir);
            // Check if directory exists
            bool dirExists(const std::string& dir);
            // Check if file exists
            bool fileExists(const std::string& dir);


            // File loading functions
            std::string loadFileStr(const std::string& fpath); // Load it as a string instead
            char* loadFileText(const std::string& fpath, size_t& fsize); // Null terminates the file text
            unsigned char* loadFileData(const std::string& path, size_t& fsize);
            // File unloading functions
            void unloadFileText(char* data);
            void unloadFileData(unsigned char* data);
            // File saving functions
            void saveFileStr(const std::string& path, const std::string& data);
            void saveFileText(const std::string& path, char* data);
            void saveFileData(const std::string& path, unsigned char* data);
            // Get file extension
            std::string getFileExtension(const std::string& path);
        };
    }
#endif