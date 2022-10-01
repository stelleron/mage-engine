#ifndef ARCANA2D_APPCONFIG
    #define ARCANA2D_APPCONFIG
    // Includes
    #include <string>
    #include "utils/Color.hpp"
    #include "utils/Vector.hpp"

    namespace arcana {
        struct AppConfig {
            int width;
            int height;
            std::string title;
            Color background_color;

            // Window settings
            bool resizable; 
            bool maximized; 
            bool fullscreen;
            bool decorated;
            bool vsync;
            bool transparent;
            bool focused;
            bool halt_while_hidden; // Set whether the app will pause while hidden

            // Framerate cap
            int fps_cap;
            // Opacity
            float opacity;
            // Min to max size
            Vector2 min_size;
            Vector2 max_size;

            // Default constructor
            AppConfig();
        };
    }
#endif