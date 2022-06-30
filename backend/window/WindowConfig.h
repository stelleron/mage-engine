#ifndef MAGE_WINDOW_CONFIG_H
    #define MAGE_WINDOW_CONFIG_H
    #include "Color.h"
    #include <string>
    namespace Mage {
        // Used to store window data
        struct WindowConfig {
            // Window configuration details
            int width;
            int height;
            std::string windowTitle;
            Color backgroundColor;

            bool windowResizable;
            bool windowMaximized;
            bool windowFullscreen;
            bool windowVSync;
        };
    }
#endif