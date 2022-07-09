#ifndef MAGE_CONFIG_H
    #define MAGE_CONFIG_H
    #include <string>
    #include "Color.h"
    // Used to configure the engine
    namespace Mage {
        struct MageConfig {
            // Window configuration details
            int width;
            int height;
            std::string windowTitle;
            Color backgroundColor;

            bool windowResizable;
            bool windowMaximized;
            bool windowFullscreen;
            bool windowVSync;

            // Resource folder location
            std::string respath;

            // Constructor/destructor
            MageConfig();
            ~MageConfig(){};
        };
    }
#endif