#ifndef ARCANA2D_EVENTDATA
    #define ARCANA2D_EVENTDATA
    #include <queue>
    #include "utils/Vector.hpp"
    
    namespace arcana {
        // Current supported keys enum
        enum Key {
            Space = 1,
            Apostrophe,
            Comma,
            Minus,
            Period,
            Slash,
            Zero,
            One,
            Two, 
            Three,
            Four,
            Five,
            Six,
            Seven,
            Eight,
            Nine,
            Semicolon,
            Equal,
            A,
            B,
            C,
            D,
            E,
            F, 
            G,
            H,
            I,
            J,
            K, 
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            LeftBracket,
            Backslash,
            RightBracket,
            GraveAccent,
            World1,
            World2,
            Escape,
            Enter,
            Tab,
            Backspace,
            Insert,
            Delete,
            Right,
            Left,
            Down,
            Up,
            PageUp,
            PageDown,
            Home,
            End,
            CapsLock,
            ScrollLock,
            NumLock,
            PrintScreen,
            Pause,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7, 
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14, 
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24, 
            F25,
            KP0,
            KP1,
            KP2,
            KP3,
            KP4,
            KP5,
            KP6,
            KP7,
            KP8,
            KP9,
            KPDecimal,
            KPDivide,
            KPMultiply,
            KPSubtract,
            KPAdd,
            KPEnter,
            KPEqual,
            LeftShift,
            LeftControl,
            LeftAlt,
            LeftSuper,
            RightShift,
            RightControl,
            RightAlt,
            RightSuper,
            Menu 
        };

        // Current supported buttons enum
        enum MouseButton {
            LeftButton = 1,
            MiddleButton,
            RightButton
        };

        // Used to store event data
        struct EventData {
            // Store window data
            struct WindowData {
                bool wasResized; // Checks if the window has been resized
                bool wasMoved; // Checks if the window has been moved
                bool isMinimized; // Checks if the window is minimized
                bool isMaximized; // Checks if the window is maximized
                Vector2 windowPos; // Stores the window position
            };
            
            // Store mouse events
            struct MouseData {
                Vector2 mousePos; 
                Vector2 mouseLastPos;
                float mScrollH;
                float mScrollV;
                bool buttonPressed[MouseButton::RightButton];
                bool buttonLastPressed[MouseButton::RightButton];
            };

            // Store keyboard events
            struct KeyboardData {
                bool keyPressed[Key::Menu];
                bool keyLastPressed[Key::Menu];
                std::queue<unsigned char> charQueue;
            };

            // Store gamepad data
            struct GamepadData {
                // TODO in a later version
            };

            WindowData windowData;
            KeyboardData keyboardData;
            MouseData mouseData;
            GamepadData gamepadData;

            // Default initialiser
            EventData();

            // Reload event data to prepare for new data
            void reload();
        };
    };
#endif