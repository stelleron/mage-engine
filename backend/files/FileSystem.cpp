#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "utils/DebugTools.h"
#include "FileSystem.h"

namespace Mage {
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

    // Gets the parent directory of the current exec., going back by a specified number
    std::string rewindPath(int val)
    {
        // First get the exec. path 
        std::string execPath = getExecPath();
        // Then parse the path to get every directory
        std::stringstream execStr(execPath);
        std::string segment;
        std::vector<std::string> seglist;
        while(std::getline(execStr, segment, '/'))
        {
            seglist.push_back(segment);
        }
        
        // Then get the parent directory 
        std::string parentDir;
        for (int x = 0; x < seglist.size() - val; x++) {
            parentDir += seglist[x];
            parentDir += "/";
        }
        return parentDir;
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