#ifndef MAGE_ARGUMENTS_HPP
    #define MAGE_ARGUMENTS_HPP
    #include "frontend/Frontend.hpp"
    #include <string>
    #include <vector>

    namespace Mage {
        // Used to store the engine arguments
        struct Argument {
            std::vector<std::string> argArray;

            Argument(int count, char** args);
        };
        // Handle the arguments
        void handleArgs(const Argument& arg, std::string& pathbuf, bool& runProj, RunType& rType);
    }
#endif