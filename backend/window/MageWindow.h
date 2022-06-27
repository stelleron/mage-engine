#ifndef MAGE_WINDOW_H
    #define MAGE_WINDOW_H
    #include "GLFW/glfw3.h"
    namespace Mage {
        class MageWindow {
        private:
            GLFWwindow* window;
        public:
            MageWindow(const WindowConfig& config);
            ~MageWindow();
        };
    }
#endif