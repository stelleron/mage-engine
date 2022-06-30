#ifndef MAGE_WINDOW_H
    #define MAGE_WINDOW_H
    #include "GLFW/glfw3.h"
    #include "WindowConfig.h"
    namespace Mage {
        class MageWindow {
        private:
            GLFWwindow* window; // The GLFW window
            Color backgroundColor; // Stores the background color of the window
            GLFWmonitor* monitor; // Stores the monitor
        public:
            MageWindow(const WindowConfig& config);
            ~MageWindow();
        };
    }
#endif