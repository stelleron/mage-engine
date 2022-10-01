#include "res/Filesystem.hpp"
#include <fstream>
#include <sstream>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "utils/Logger.hpp"
#include <stdlib.h>

namespace arcana {
    namespace filesystem {
        std::string currentWorkingDir = "";

        void setDir(const std::string& dir) {
            if (!dirExists(dir)) {
                LOG("Filesystem: Directory does not exist!");
                exit(1);
            }

            currentWorkingDir = dir;
            if (dir[-1] != '/') {
                currentWorkingDir += '/';
            }
        }

        bool dirExists(const std::string& dir) {
            struct stat buffer;
            stat(dir.c_str(), &buffer);
            if (buffer.st_mode & S_IFDIR) {
                return true;
            }
            else {
                return false;
            }
        }

        bool fileExists(const std::string& path) {
            struct stat buffer;
            stat(path.c_str(), &buffer);
            if (buffer.st_mode & S_IFREG) {
                return true;
            }
            else {
                return false;
            }
        }

        std::string loadFileStr(const std::string& dir) {
            if (!fileExists(dir)) {
                LOG("Filesystem: File does not exist!");
                exit(1);
            }

            std::string path = currentWorkingDir;
            path += dir;
            std::ifstream fin(path, std::ios::in);
            std::stringstream buffer;
            buffer << fin.rdbuf() << '\0';
            return buffer.str();
        }

        char* loadFileText(const std::string& dir, size_t& fsize) {
            if (!fileExists(dir)) {
                LOG("Filesystem: File does not exist!");
                exit(1);
            }

            std::string source = loadFileStr(dir);
            char* buffer = new char[source.size()];
            fsize = source.size() * sizeof(char);
            memcpy( buffer, source.c_str(), source.size() );
            return buffer;
        }

        unsigned char* loadFileData(const std::string& dir, size_t& fsize) {
            if (!fileExists(dir)) {
                LOG("Filesystem: File does not exist!");
                exit(1);
            }

            std::string path = currentWorkingDir;
            path += dir;
            FILE *file = fopen(path.c_str(), "rb");
            fseek(file, 0, SEEK_END);
            int size = ftell(file);
            fseek(file, 0, SEEK_SET);
            unsigned char* data = new unsigned char[size];
            unsigned int count = fread(data, 1, size, file);
            fsize = count;
            fclose(file);
            return data;
        }

        void unloadFileText(char* data) {
            delete[] data;
        }

        void unloadFileData(unsigned char* data) {
            delete[] data;
        }
        void saveFileStr(const std::string& path, const std::string& data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        void saveFileText(const std::string& path, char* data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        void saveFileData(const std::string& path, unsigned char* data) {
            std::string fpath = currentWorkingDir;
            fpath += path;
            std::ofstream output(fpath, std::ios::out);
            output << data;
        }
        std::string getFileExtension(const std::string& path) {
            return path.substr(path.find_last_of(".") + 1);
        }
    }
}