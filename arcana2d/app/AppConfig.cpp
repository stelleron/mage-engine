#include "app/AppConfig.hpp"
#include <GLFW/glfw3.h>

namespace arcana {
    AppConfig::AppConfig() {
        width = 800;
        height = 600;
        title = "Untitled Game";
        background_color = Color::RGB(20, 20, 20);

        resizable = false;
        fullscreen = false;
        decorated = true;
        maximized = false;
        vsync = true;
        transparent = false;
        focused = true;
        halt_while_hidden = true;

        fps_cap = 60;
        opacity = 1.0f;
        min_size = Vector2(GLFW_DONT_CARE, GLFW_DONT_CARE);
        max_size = Vector2(GLFW_DONT_CARE, GLFW_DONT_CARE);
    }
}