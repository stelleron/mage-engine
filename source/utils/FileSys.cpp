#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "utils/DebugTools.hpp"
#include "utils/FileSys.hpp"

namespace Mage {
    PathType getPathType(const char* path) {
        struct stat buffer;
        stat(path, &buffer);
        if (buffer.st_mode & S_IFREG ) 
            return FILE_PATH;
        else if (buffer.st_mode & S_IFDIR )
            return DIR_PATH;
        else
            return UNKNOWN_PATH;
    }

    std::string getExecPath()
    { 
        char* path = NULL;
        int length, dirname_length;
        int i;
        length = wai_getExecutablePath(NULL, 0, &dirname_length);
        if (length > 0) {
            path = new char[length + 1];
            if (!path) {abort();}
            wai_getExecutablePath(path, length, &dirname_length);
            path[length] = '\0';
            path[dirname_length] = '\0';
            std::string strpath(path);
            delete[] path;
            return strpath;
        }
        else {
            return std::string("Unable to get the exec path!");
        }
    }

    // Gets the parent directory of a given path, going back by a specified number
    /// NOTE: REFACTOR HERE
    std::string rewindPath(const std::string& path, int val)
    {
        // Parse the path to get every directory
        std::stringstream strstream(path);
        std::string segment;
        std::vector<std::string> seglist;
        while(std::getline(strstream, segment, '/'))
        {
            seglist.push_back(segment);
        }
        // Then get the parent directory 
        std::string parentDir = "";
        for (int x = 0; x < seglist.size() - val; x++) {
 
            parentDir += seglist[x];        
            parentDir += "/";
        }
        return parentDir;
    }

    std::string getPathEnd(const std::string& path) {
        // Parse the path to get every directory
        std::stringstream execStr(path);
        std::string segment;
        std::vector<std::string> seglist;
        while(std::getline(execStr, segment, '/'))
        {
            seglist.push_back(segment);
        }
        MAGE_OUTPUT(seglist[seglist.size() - 1].c_str());
        return seglist[seglist.size() - 1];
    }

    // Load a file and get it's content(heap allocated)
    const char* loadFile(std::string& path) 
    {
        std::ifstream fileData;
        fileData.open(path, std::ios::in);
        std::stringstream buffer;
        buffer << fileData.rdbuf() << '\0';
        fileData.close();
        std::string source = buffer.str();
        char* cbuffer = (char*) malloc( source.size() );
        assert(cbuffer != nullptr);
        memcpy(cbuffer, source.c_str(), source.size() );
        return cbuffer;
    }

    const char* loadFile(const char* path) {
        std::ifstream fileData;
        fileData.open(path, std::ios::in);
        std::stringstream buffer;
        buffer << fileData.rdbuf() << '\0';
        fileData.close();
        std::string source = buffer.str();
        char* cbuffer = (char*) malloc( source.size() );
        assert(cbuffer != nullptr);
        memcpy(cbuffer, source.c_str(), source.size() );
        return cbuffer;
    }

    void addSlash(std::string& path) {
        if (path.back() != '/') {
            path.append("/");
        }
    }

    std::string getFileExtension(const std::string& filepath) {
        std::string ext = filepath.substr(filepath.find_last_of(".") + 1);
        return ext;
    }

    std::string removePartOfFilePath(const std::string& src, const std::string& remove_str) {
        int rem_len = remove_str.size();
        std::string subPath = src.substr(rem_len);
        return subPath;
    }

    void unloadFile(const char* source) {
        free((void*)source);
    }
    
    File::File(const char* path) {
        source = (char*)loadFile(path);
    }

    File::~File() {
        unloadFile(source);
    }
}