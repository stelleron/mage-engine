#include <glad/glad.h>
#include "window/Window.hpp"
#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    Window::Window() {
        glfwDefaultWindowHints();
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        LOG("Arcana2D: Initialised GLFW!");
    }

    void Window::init(const AppConfig& config) {
        // Set some flags
        glfwWindowHint(GLFW_RESIZABLE, config.resizable);
        glfwWindowHint(GLFW_DECORATED, config.decorated);
        glfwWindowHint(GLFW_MAXIMIZED, config.maximized);
        glfwWindowHint(GLFW_FOCUSED, config.focused);
        glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, config.transparent);

        // Check if fullscreen enabled before creating the window
        if (config.fullscreen) {
            window = glfwCreateWindow(config.width, config.height, 
                                  config.title.c_str(), glfwGetPrimaryMonitor(), NULL);
        }
        else {
            window = glfwCreateWindow(config.width, config.height, 
                                  config.title.c_str(), NULL, NULL);
        }
        if (window == NULL) {
            ERROR("Arcana2D: Could not initialise a window!");
            exit(1);
        }
        else {
            LOG("Arcana2D: Initialised the window!");
        }

        // Set the window to the current context
        glfwMakeContextCurrent(window);

        // Initialise GLAD
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
            ERROR("Arcana2D: Could not initialise GLAD!");
            exit(1);
        }
        else {
            LOG("Arcana2D: Initialised GLAD!");
        }
        
        // Enable alpha blending and depth
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        // And set the OpenGL viewport
        int left, top, right, bottom;
        glfwGetWindowFrameSize(window, &left, &top, &right, &bottom);   
        glViewport(0, 0, right - left, bottom - top);

        // And set the background color
        background_color = config.background_color;

        // And set window size limits
        glfwSetWindowSizeLimits(window, config.min_size.x, config.min_size.y, config.max_size.x, config.max_size.y);
        min_size = Vector2(config.min_size.x, config.min_size.y);
        max_size = Vector2(config.max_size.x, config.max_size.y);

        // And opacity
        glfwSetWindowOpacity(window, config.opacity);

        // Finally set vsync
        if (config.vsync) 
            glfwSwapInterval(1);
        else
            glfwSwapInterval(0);

        halt_while_hidden = config.halt_while_hidden;
        setCallbacks(window);
    }

    void Window::pollEvents() {
        glfwPollEvents();
    }

    bool Window::shouldClose() {
        return glfwWindowShouldClose(window);
    }

    void Window::close() {
        glfwSetWindowShouldClose(window, true);
        LOG("Window: Closing the window!");
    }

    void Window::keepOpen() {
        glfwSetWindowShouldClose(window, false);
        LOG("Window: Keeping the window open!");
    }

    bool Window::isActive() {
        #ifdef ENABLE_ARCANA_LOGGER
            static bool loggedActive = false;
            static bool loggedInactive = false;
        #endif

        if (halt_while_hidden) {
            if (!glfwGetWindowAttrib(window, GLFW_VISIBLE)) {
                #ifdef ENABLE_ARCANA_LOGGER
                    if (!loggedActive) {
                        loggedActive = true;
                        loggedInactive = false;
                        LOG("Window: Is currently hidden and inactive!");
                    }
                #endif
                return false;
            }
            else {
                #ifdef ENABLE_ARCANA_LOGGER
                    if (!loggedInactive) {
                        loggedInactive = true;
                        loggedActive = false;
                        LOG("Window: Is currently active!");
                    }
                #endif
                return true;
            }
        }
        return true;
    }

    void Window::fill() {
        glClearColor(COLOR_TO_FLOAT(background_color));
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::swapBuffer() {
        // And swap buffers
        glfwSwapBuffers(window);
    }

    void Window::setData(void* ptr) {
        glfwSetWindowUserPointer(window, ptr);
    }

    void Window::setIcon(int width, int height, unsigned char* data) {
        GLFWimage image;
        image.width = width;
        image.height = height;
        image.pixels = data;
        glfwSetWindowIcon(window, 1, &image);
    }
    
    void* Window::getData() {
        return glfwGetWindowUserPointer(window);
    }   

    void Window::updateTitle(const char* title) {
        glfwSetWindowTitle(window, title);
    }

    Window::~Window() {
        // Destroying for proper practice
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}