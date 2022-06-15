#include "MageConfig.h"
namespace Mage {
    MageConfig::MageConfig() {
        // Default window configs.
        width = 800;
        height = 600;
        windowTitle = "Untitled Game";
        backgroundColor = Color(20, 20, 20, 255);
        windowResizable = false;
        windowMaximized = false;
        windowFullscreen = false;
        windowVSync = true;
        respath = "";
    }

    

    MageConfig::~MageConfig() {

    }
}