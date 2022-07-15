#include "Main.hpp"

using namespace Mage;

#ifdef DEBUG
    int main(int argc, char** argv) {
        // First initialise the logger
        DebugTools::Init();
        // Initialiser arguments
        std::string pathdir;
        RunType rType;
        bool runGame = false;
        {
            // Then convert the arguments to an easy to read format
            Argument arg(argc, argv);
            // And then process them
            handleArgs(arg, pathdir, runGame, rType);
        }
        if (runGame) {
            if (rType == RUN_UNKNOWN) {
                MAGE_ERROR("Qutting the engine..");
                return 1;
            }
            MAGE_INFO("Frontend: Running project in current directory: {0}", pathdir.c_str());
            Frontend frontend(pathdir, rType);
            MAGE_INFO("");
        }
    }
    
#else 
    int main() {
        Frontend(getExecPath(), RUN_STORED);
    }
#endif

