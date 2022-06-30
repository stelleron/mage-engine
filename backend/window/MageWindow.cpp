#include "MageWindow.h"
#include "DebugTools.h"
namespace Mage {
    MageWindow::MageWindow(const WindowConfig& config) {
        // Initialise the OpenGL context here
        glfwInit();       
        glfwDefaultWindowHints();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        // Then set the window flags
        glfwWindowHint(GLFW_RESIZABLE, config.windowResizable);
        glfwWindowHint(GLFW_MAXIMIZED, config.windowMaximized);
        // Then initialise the window and set it as the current context
    }

    MageWindow::~MageWindow() {

    }
}