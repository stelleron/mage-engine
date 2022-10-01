#ifndef ARCANA2D_GAME_CONTEXT
    #define ARCANA2D_GAME_CONTEXT

    #include "audio/Audio.hpp"
    #include "camera/Camera.hpp"
    #include "window/Window.hpp"
    #include "input/EventData.hpp"

    namespace arcana {
        // Used to store the game context
        class GameContext {

            // Window API struct
            struct CtxWindow {
                private:
                    EventData* event_data;
                    Window* window;
                public:
                    // Set the window pointer
                    inline void set(Window& window) {this->window = &window;} 
                    // Set the event data pointer 
                    inline void setEventData(EventData& events) {event_data = &events;}

                    inline bool wasResized() {return event_data->windowData.wasResized;} // Was the window resized last frame?
                    inline bool wasMoved() {return event_data->windowData.wasMoved;} // Was the window moved last frame?
                    inline bool isMinimized() {return event_data->windowData.isMinimized;} // Is the window minimized?
                    inline bool isMaxmized() {return event_data->windowData.isMaximized;} // Is the window maximized?
                    inline Vector2 getPos() {return event_data->windowData.windowPos;} // Gets the window position

                    Vector2 getWindowSize();
                    void setMinWindowSize(int min_width, int min_height);
                    void setMaxWindowSize(int max_width, int max_height);
                    void setWindowPos(int x, int y);
                    void setWindowPos(Vector2 pos);
                    void restoreWindow();
                    void minimizeWindow();
                    void maximizeWindow();
                    void updateTitle(const char* title);
                    void close() {window->close();}
            };

            // Time API struct
            struct CtxTimer {
                private:
                    float dtime;
                public: 
                    CtxTimer() {dtime = 0.0f;}
                    inline void set(float dtime) {this->dtime = dtime;}
                    inline float dt() {return dtime;}
                    inline int fps() {return (int)1.0f/dtime;}
            };

            // Camera API struct 
            struct CtxCamera {
                private:
                    Camera* camera;
                public: 
                    inline void set(Camera& camera) {this->camera = &camera;}
                    inline Camera* get() {return camera;}

            };

            // Events API struct
            struct CtxEvents {
                private:
                    EventData events;
                public:
                    inline EventData& get() {return events;}
                    inline void reload() {events.reload();}
            };

            // Keyboard API struct
            struct CtxKeyboard {
                private:  
                    EventData* event_data;
                public:
                    inline void setEventData(EventData& events) {event_data = &events;}
                    inline bool isPressed(Key key) {
                    if (event_data->keyboardData.keyPressed[key - 1] && !event_data->keyboardData.keyLastPressed[key - 1]) {
                        return true;
                    }
                    return false;
                    }

                    // If the key was just released
                    inline bool isReleased(Key key) {
                        if (!event_data->keyboardData.keyPressed[key - 1] && event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the key is being held down
                    inline bool isHeld(Key key) {
                        if (event_data->keyboardData.keyPressed[key - 1] && event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the key isn't being pressed at all
                    inline bool isUp(Key key) {
                        if (!event_data->keyboardData.keyPressed[key - 1] && !event_data->keyboardData.keyLastPressed[key - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // Get typed characters one at a time
                    inline unsigned char getCharPressed() {
                        if (event_data->keyboardData.charQueue.size() > 0) {
                            unsigned char val = event_data->keyboardData.charQueue.front();
                            event_data->keyboardData.charQueue.pop();
                            return val;
                        }
                        else {
                            return 0;
                        }
                    }
            };

            // Mouse API struct
            struct CtxMouse {
                private:  
                    EventData* event_data;
                public:
                    inline void setEventData(EventData& events) {event_data = &events;} 
                    inline bool isPressed(MouseButton button) {
                    if (event_data->mouseData.buttonPressed[button - 1] && !event_data->mouseData.buttonLastPressed[button - 1]) {
                        return true;
                    }
                    return false;
                    }

                    // If the mouse button was just released
                    inline bool isReleased(MouseButton button) {
                        if (!event_data->mouseData.buttonPressed[button - 1] && event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the mouse button was being held
                    inline bool isHeld(MouseButton button) {
                        if (event_data->mouseData.buttonPressed[button - 1] && event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // If the mouse button is up
                    inline bool isUp(MouseButton button) {
                        if (!event_data->mouseData.buttonPressed[button - 1] && !event_data->mouseData.buttonLastPressed[button - 1]) {
                            return true;
                        }
                        return false;
                    }

                    // Get mouse position 
                    inline Vector2 getPos() {return event_data->mouseData.mousePos;}

                    // Get mouse delta
                    inline Vector2 getDeltaPos() {return Vector2(event_data->mouseData.mousePos.x - event_data->mouseData.mouseLastPos.x, 
                                                    event_data->mouseData.mousePos.y - event_data->mouseData.mouseLastPos.y);}

                    // Get vertical scroll
                    inline float getVerticalScroll() {return event_data->mouseData.mScrollV;}

                    // Get scroll vector
                    inline Vector2 getScroll() {return Vector2(event_data->mouseData.mScrollH, event_data->mouseData.mScrollV);}
            };

            private:

            public:
                CtxWindow window;
                CtxTimer timer;
                CtxCamera camera;
                CtxEvents events;
                CtxKeyboard keyboard;
                CtxMouse mouse;
                AudioContext audio;

                // Constructor
                GameContext();
                // Destructor
                ~GameContext();

                
        };
    }
#endif