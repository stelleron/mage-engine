#include "utils/DebugTools.hpp"
#include "utils/Base.hpp"
#include "utils/FileSys.hpp"

#include "frontend/Arguments.hpp"

#include "datapak.hpp"
#include <filesystem>

namespace Mage
{
    //TODO: Fix this!
    void exploreDir(std::string& dirname, std::vector<std::string> *buffer, std::string& rootpath) {
    // Explore the directory recursively
        if (getPathType(dirname.c_str()) == DIR_PATH) {
            // Now loop through the folder
            for (const auto& entry : std::filesystem::directory_iterator(dirname)) {
                if (getPathType(entry.path().c_str()) == FILE_PATH) {
                    std::string newPath = entry.path().string();
                    removePartOfFilePath(newPath, dirname);
                    buffer->push_back(entry.path().c_str());
                }
                else if (getPathType(entry.path().c_str()) == DIR_PATH) {
                    std::string newRootPath = rootpath + dirname;
                    std::string dirPath = entry.path().string();
                    exploreDir(dirPath, buffer, newRootPath);
                }
            }
        }
        else {
            MAGE_ERROR("Error: Given invalid path! Path must be an existing directory");
        }
    }

    Argument::Argument(int count, char** args) {
        if (count < 2) {
            MAGE_ERROR("Error: Too few arguments passed!");
        }
        else {
            argArray.resize(count - 1);
            for (int x = 1; x < count; x++) {
                argArray[x - 1] = args[x];
            }
        }
    } 

    RunType getProjectType(const std::string& path) {
        // First get the path type
        PathType pType = getPathType(path.c_str());
        // Then check what type of project it is
        switch (pType) {
            case UNKNOWN_PATH: return RUN_UNKNOWN; break;
            case DIR_PATH: {
                std::string modPath = path;
                addSlash(modPath);
                modPath += "main.wren";
                PathType mainFileExists = getPathType(modPath.c_str());
                if (mainFileExists == FILE_PATH) {
                    return RUN_PROJECT; break;
                }
                else {
                    MAGE_ERROR("Error: main.wren not in the given directory!");
                    return RUN_UNKNOWN; break;
                }
            }
            case FILE_PATH: {
                // First get the end directory of the path
                std::string pEnd = getPathEnd(path);
                // Then get the file extension and verify that it is a .mageproj
                MAGE_INFO("{0}", pEnd);
                if (getFileExtension(pEnd) == "mageproj") {
                    return RUN_PACKAGE; break;
                }
                else {
                    MAGE_ERROR("Error: A .mageproj file has not been provided!");
                    return RUN_UNKNOWN; break;
                }
            }
            default: break;
        }
    }

    void handleArgs(const Argument& arg, std::string& pathbuf, bool& runProj, RunType& rType) {
        // Check if the command was merely a version request
        if (arg.argArray[0] == "version") {
            MAGE_INFO("Current Version: {0}", ENGINE_VERSION);
        }
        // Else check if the engine was supposed to run a Wren project
        else if (arg.argArray[0] == "run") {
            // Is it in the current directory or in a given directory
            if (arg.argArray.size() == 1) {
                pathbuf = std::filesystem::current_path();
            }
            else if (arg.argArray.size() == 2) {
                pathbuf = arg.argArray[1];
            }
            rType = getProjectType(pathbuf);
            runProj = true;
        }
        // Else check if a request was made to package a directory
        else if (arg.argArray[0] == "package") {
            if (arg.argArray.size() == 2) {
                pathbuf = arg.argArray[1];
                std::string pakpath = rewindPath(pathbuf, 1);
                pakpath += "game.mageproj";
                // Create the game.mageproj
                MAGE_INFO("Creating a .mageproj file in the directory: {0}...", pathbuf.c_str());
                Datapak dat(pakpath.c_str());
                dat.purge();
                // Now add all files from the given directory to it
                std::string rootpath = "";
                std::vector<std::string> filenameBuffer;
                exploreDir(pathbuf, &filenameBuffer, rootpath);
                MAGE_INFO("Found {0} files. Reading them all..", filenameBuffer.size());
                std::string fileSrc;
                int x;
                for (x = 0; x < filenameBuffer.size(); x++) {
                    fileSrc = loadFile(filenameBuffer[x]);
                    dat.write(filenameBuffer[x].c_str(), fileSrc);
                }
                dat.close();

                if (x != filenameBuffer.size()) {
                    MAGE_ERROR("Error: For some reason, {0} files were unable to be packaged!", filenameBuffer.size() - x);
                }
            }
            else {
                MAGE_ERROR("Error: No path to package!");
            }
        }
    }
} 
