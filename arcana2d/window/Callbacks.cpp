#include <GLFW/glfw3.h>
#include "window/Callbacks.hpp"
#include "utils/Logger.hpp"
#include "context/GameContext.hpp"

// Macro defines
#define KEY_MAP_FUNC(glfw_key, arcana_key) case glfw_key: do {if(action == GLFW_PRESS) {(ctx->events.get()).keyboardData.keyPressed[arcana_key - 1] = true;} else if(action == GLFW_RELEASE) {(ctx->events.get()).keyboardData.keyPressed[arcana_key - 1] = false;}}  while (false); break;
#define MOUSE_MAP_FUNC(glfw_button, arcana_button) case glfw_button: do {if(action == GLFW_PRESS) {(ctx->events.get()).mouseData.buttonPressed[arcana_button - 1] = true;} else if(action == GLFW_RELEASE) {(ctx->events.get()).mouseData.buttonPressed[arcana_button - 1] = false;}}  while (false); break;

namespace arcana {
    void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
    }

    void windowSizeCallback(GLFWwindow* window, int width, int height) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Resize the camera
        (ctx->camera.get())->dimensions = Vector2(width, height);
        // Modify window data
        (ctx->events.get()).windowData.wasResized = true;
    }

    void windowPosCallback(GLFWwindow* window, int xpos, int ypos) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        // Modify window data
        (ctx->events.get()).windowData.wasMoved = true;
        (ctx->events.get()).windowData.windowPos = {xpos, ypos};
    }

    void windowIconifyCallback(GLFWwindow* window, int iconified) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->events.get()).windowData.isMinimized = iconified;
    }

    void windowMaxmizeCallback(GLFWwindow* window, int maximized) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->events.get()).windowData.isMaximized = maximized;        
    }

    void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        // Match the GLFW key to the Arcana2D key
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        switch(key) {
            KEY_MAP_FUNC(GLFW_KEY_SPACE, Key::Space);
            KEY_MAP_FUNC(GLFW_KEY_APOSTROPHE, Key::Apostrophe);
            KEY_MAP_FUNC(GLFW_KEY_COMMA, Key::Comma);
            KEY_MAP_FUNC(GLFW_KEY_MINUS, Key::Minus);
            KEY_MAP_FUNC(GLFW_KEY_PERIOD, Key::Period);
            KEY_MAP_FUNC(GLFW_KEY_SLASH, Key::Slash);
            KEY_MAP_FUNC(GLFW_KEY_0, Key::Zero);
            KEY_MAP_FUNC(GLFW_KEY_1, Key::One);
            KEY_MAP_FUNC(GLFW_KEY_2, Key::Two);
            KEY_MAP_FUNC(GLFW_KEY_3, Key::Three);
            KEY_MAP_FUNC(GLFW_KEY_4, Key::Four);
            KEY_MAP_FUNC(GLFW_KEY_5, Key::Five);
            KEY_MAP_FUNC(GLFW_KEY_6, Key::Six);
            KEY_MAP_FUNC(GLFW_KEY_7, Key::Seven);
            KEY_MAP_FUNC(GLFW_KEY_8, Key::Eight);
            KEY_MAP_FUNC(GLFW_KEY_9, Key::Nine);
            KEY_MAP_FUNC(GLFW_KEY_SEMICOLON, Key::Semicolon);
            KEY_MAP_FUNC(GLFW_KEY_EQUAL, Key::Equal);
            KEY_MAP_FUNC(GLFW_KEY_A, Key::A);
            KEY_MAP_FUNC(GLFW_KEY_B, Key::B);
            KEY_MAP_FUNC(GLFW_KEY_C, Key::C);
            KEY_MAP_FUNC(GLFW_KEY_D, Key::D);
            KEY_MAP_FUNC(GLFW_KEY_E, Key::E);
            KEY_MAP_FUNC(GLFW_KEY_F, Key::F);
            KEY_MAP_FUNC(GLFW_KEY_G, Key::G);
            KEY_MAP_FUNC(GLFW_KEY_H, Key::H);
            KEY_MAP_FUNC(GLFW_KEY_I, Key::I);
            KEY_MAP_FUNC(GLFW_KEY_J, Key::J);
            KEY_MAP_FUNC(GLFW_KEY_K, Key::K);
            KEY_MAP_FUNC(GLFW_KEY_L, Key::L);
            KEY_MAP_FUNC(GLFW_KEY_M, Key::M);
            KEY_MAP_FUNC(GLFW_KEY_N, Key::N);
            KEY_MAP_FUNC(GLFW_KEY_O, Key::O);
            KEY_MAP_FUNC(GLFW_KEY_P, Key::P);
            KEY_MAP_FUNC(GLFW_KEY_Q, Key::Q);
            KEY_MAP_FUNC(GLFW_KEY_R, Key::R);
            KEY_MAP_FUNC(GLFW_KEY_S, Key::S);
            KEY_MAP_FUNC(GLFW_KEY_T, Key::T);
            KEY_MAP_FUNC(GLFW_KEY_U, Key::U);
            KEY_MAP_FUNC(GLFW_KEY_V, Key::V);
            KEY_MAP_FUNC(GLFW_KEY_W, Key::W);
            KEY_MAP_FUNC(GLFW_KEY_X, Key::X);
            KEY_MAP_FUNC(GLFW_KEY_Y, Key::Y);
            KEY_MAP_FUNC(GLFW_KEY_Z, Key::Z);
            KEY_MAP_FUNC(GLFW_KEY_LEFT_BRACKET, Key::LeftBracket);
            KEY_MAP_FUNC(GLFW_KEY_BACKSLASH, Key::Backslash);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT_BRACKET, Key::RightBracket);
            KEY_MAP_FUNC(GLFW_KEY_GRAVE_ACCENT, Key::GraveAccent);
            KEY_MAP_FUNC(GLFW_KEY_WORLD_1, Key::World1);
            KEY_MAP_FUNC(GLFW_KEY_WORLD_2, Key::World2);
            KEY_MAP_FUNC(GLFW_KEY_ESCAPE, Key::Escape);
            KEY_MAP_FUNC(GLFW_KEY_ENTER, Key::Enter);
            KEY_MAP_FUNC(GLFW_KEY_TAB, Key::Tab);
            KEY_MAP_FUNC(GLFW_KEY_BACKSPACE, Key::Backspace);
            KEY_MAP_FUNC(GLFW_KEY_INSERT, Key::Insert);
            KEY_MAP_FUNC(GLFW_KEY_DELETE, Key::Delete);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT, Key::Right);
            KEY_MAP_FUNC(GLFW_KEY_LEFT, Key::Left);
            KEY_MAP_FUNC(GLFW_KEY_DOWN, Key::Down);
            KEY_MAP_FUNC(GLFW_KEY_UP, Key::Up);
            KEY_MAP_FUNC(GLFW_KEY_PAGE_UP, Key::PageUp);
            KEY_MAP_FUNC(GLFW_KEY_PAGE_DOWN, Key::PageDown);
            KEY_MAP_FUNC(GLFW_KEY_HOME, Key::Home);
            KEY_MAP_FUNC(GLFW_KEY_END, Key::End);
            KEY_MAP_FUNC(GLFW_KEY_CAPS_LOCK, Key::CapsLock);
            KEY_MAP_FUNC(GLFW_KEY_SCROLL_LOCK, Key::ScrollLock);
            KEY_MAP_FUNC(GLFW_KEY_NUM_LOCK, Key::NumLock);
            KEY_MAP_FUNC(GLFW_KEY_PRINT_SCREEN, Key::PrintScreen);
            KEY_MAP_FUNC(GLFW_KEY_PAUSE, Key::Pause);
            KEY_MAP_FUNC(GLFW_KEY_F1, Key::F1);
            KEY_MAP_FUNC(GLFW_KEY_F2, Key::F2);
            KEY_MAP_FUNC(GLFW_KEY_F3, Key::F3);
            KEY_MAP_FUNC(GLFW_KEY_F4, Key::F4);
            KEY_MAP_FUNC(GLFW_KEY_F5, Key::F5);
            KEY_MAP_FUNC(GLFW_KEY_F6, Key::F6);
            KEY_MAP_FUNC(GLFW_KEY_F7, Key::F7);
            KEY_MAP_FUNC(GLFW_KEY_F8, Key::F8);
            KEY_MAP_FUNC(GLFW_KEY_F9, Key::F9);
            KEY_MAP_FUNC(GLFW_KEY_F10, Key::F10);
            KEY_MAP_FUNC(GLFW_KEY_F11, Key::F11);
            KEY_MAP_FUNC(GLFW_KEY_F12, Key::F12);
            KEY_MAP_FUNC(GLFW_KEY_F13, Key::F13);
            KEY_MAP_FUNC(GLFW_KEY_F14, Key::F14);
            KEY_MAP_FUNC(GLFW_KEY_F15, Key::F15);
            KEY_MAP_FUNC(GLFW_KEY_F16, Key::F16);
            KEY_MAP_FUNC(GLFW_KEY_F17, Key::F17);
            KEY_MAP_FUNC(GLFW_KEY_F18, Key::F18);
            KEY_MAP_FUNC(GLFW_KEY_F19, Key::F19);
            KEY_MAP_FUNC(GLFW_KEY_F20, Key::F20);
            KEY_MAP_FUNC(GLFW_KEY_F21, Key::F21);
            KEY_MAP_FUNC(GLFW_KEY_F22, Key::F22);
            KEY_MAP_FUNC(GLFW_KEY_F23, Key::F23);
            KEY_MAP_FUNC(GLFW_KEY_F24, Key::F24);
            KEY_MAP_FUNC(GLFW_KEY_F25, Key::F25);
            KEY_MAP_FUNC(GLFW_KEY_KP_0, Key::KP0);
            KEY_MAP_FUNC(GLFW_KEY_KP_1, Key::KP1);
            KEY_MAP_FUNC(GLFW_KEY_KP_2, Key::KP2);
            KEY_MAP_FUNC(GLFW_KEY_KP_3, Key::KP3);
            KEY_MAP_FUNC(GLFW_KEY_KP_4, Key::KP4);
            KEY_MAP_FUNC(GLFW_KEY_KP_5, Key::KP5);
            KEY_MAP_FUNC(GLFW_KEY_KP_6, Key::KP6);
            KEY_MAP_FUNC(GLFW_KEY_KP_7, Key::KP7);
            KEY_MAP_FUNC(GLFW_KEY_KP_8, Key::KP8);
            KEY_MAP_FUNC(GLFW_KEY_KP_9, Key::KP9);
            KEY_MAP_FUNC(GLFW_KEY_KP_DECIMAL, Key::KPDecimal);
            KEY_MAP_FUNC(GLFW_KEY_KP_DIVIDE, Key::KPDivide);
            KEY_MAP_FUNC(GLFW_KEY_KP_MULTIPLY, Key::KPMultiply);
            KEY_MAP_FUNC(GLFW_KEY_KP_SUBTRACT, Key::KPSubtract);
            KEY_MAP_FUNC(GLFW_KEY_KP_ADD, Key::KPAdd);
            KEY_MAP_FUNC(GLFW_KEY_KP_ENTER, Key::KPEnter);
            KEY_MAP_FUNC(GLFW_KEY_KP_EQUAL, Key::KPEqual);
            KEY_MAP_FUNC(GLFW_KEY_LEFT_SHIFT, Key::LeftShift);
            KEY_MAP_FUNC(GLFW_KEY_LEFT_CONTROL, Key::LeftControl);
            KEY_MAP_FUNC(GLFW_KEY_LEFT_ALT, Key::LeftAlt);
            KEY_MAP_FUNC(GLFW_KEY_LEFT_SUPER, Key::LeftSuper);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT_SHIFT, Key::RightShift);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT_CONTROL, Key::RightControl);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT_ALT, Key::RightAlt);
            KEY_MAP_FUNC(GLFW_KEY_RIGHT_SUPER, Key::RightSuper);
            KEY_MAP_FUNC(GLFW_KEY_MENU, Key::Menu);
            default: break;
        }
    }

    void charCallback(GLFWwindow* window, unsigned int codepoint) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->events.get()).keyboardData.charQueue.push(codepoint);
    }

    void mouseButtonCallback(GLFWwindow* window,int button, int action, int mods) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        switch (button) {
            MOUSE_MAP_FUNC(GLFW_MOUSE_BUTTON_LEFT, MouseButton::LeftButton);
            MOUSE_MAP_FUNC(GLFW_MOUSE_BUTTON_MIDDLE, MouseButton::MiddleButton);
            MOUSE_MAP_FUNC(GLFW_MOUSE_BUTTON_RIGHT, MouseButton::RightButton);
            default: break;
        }
    }

    void mousePosCallback(GLFWwindow* window, double xpos, double ypos) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->events.get()).mouseData.mousePos = {xpos, ypos};
    }

    void mouseScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
        GameContext* ctx = (GameContext*)glfwGetWindowUserPointer(window);
        (ctx->events.get()).mouseData.mScrollH = xoffset;
        (ctx->events.get()).mouseData.mScrollV = yoffset;
    }

    void setCallbacks(GLFWwindow* window) {
        glfwSetWindowIconifyCallback(window, windowIconifyCallback);
        glfwSetWindowMaximizeCallback(window, windowMaxmizeCallback);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
        glfwSetWindowSizeCallback(window, windowSizeCallback);
        glfwSetWindowPosCallback(window, windowPosCallback);
        glfwSetKeyCallback(window, keyboardCallback);
        glfwSetCharCallback(window, charCallback);
        glfwSetMouseButtonCallback(window, mouseButtonCallback);
        glfwSetCursorPosCallback(window, mousePosCallback);
        glfwSetScrollCallback(window, mouseScrollCallback);
        LOG("Events: Set all callbacks!");
    }
}
