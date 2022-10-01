#ifndef ARCANA2D_WINDOW
    #define ARCANA2D_WINDOW

    // Includes
    #include <GLFW/glfw3.h>
    #include "utils/Vector.hpp"
    #include "app/AppConfig.hpp"

    namespace arcana {
        // Used to create a window object
        class Window {
            private: 
                GLFWwindow* window;
                Color background_color;
                bool halt_while_hidden;

                Vector2 min_size;
                Vector2 max_size;
            public: 
                // Constructor/destructor
                Window();
                ~Window();

                // Window initialiser
                void init(const AppConfig& config);

                // Check if the window should close
                bool shouldClose();
                // Close the window
                void close();
                // Keep the window open
                void keepOpen();
                // Check if the window is active
                bool isActive();
                // Poll events
                void pollEvents();
                // Clear the framebuffer with the stored background color
                void fill();
                // Swap buffers on the window
                void swapBuffer();

                // Set the window user data
                void setData(void* ptr);
                // Get the window user data
                void* getData();

                // Set the title of the window
                void updateTitle(const char* title);
                // Set the icon of the window
                void setIcon(int width, int height, unsigned char* data);

                // Get the size of the window
                inline Vector2 getWindowSize() {int width, height; glfwGetWindowSize(window, &width, &height); return Vector2(width, height);}
                // Set size limits for the window
                inline void setMinSize(Vector2 minDim) {glfwSetWindowSizeLimits(window, minDim.x, minDim.y, max_size.x, max_size.y); min_size = minDim;}
                inline void setMaxSize(Vector2 maxDim) {glfwSetWindowSizeLimits(window, min_size.x, min_size.y, maxDim.x, maxDim.y); max_size = maxDim;}
                // Set window positions
                inline void setWindowPos(Vector2 windowPos) {glfwSetWindowPos(window, windowPos.x, windowPos.y);}
                // Restore the window
                inline void restore() {glfwRestoreWindow(window);}
                // Iconify the window
                inline void minimize() {glfwIconifyWindow(window);}; 
                // Maximize the window
                inline void maximize() {glfwMaximizeWindow(window);}
        };
    }
#endif