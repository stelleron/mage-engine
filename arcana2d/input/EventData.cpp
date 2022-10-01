#include "input/EventData.hpp"
#include "utils/Logger.hpp"

namespace arcana {
    EventData::EventData() {
        // Reset window events
        windowData.wasResized = false;
        windowData.wasMoved = false;

        // Reset keyboard events
        for (int x = 0; x < Key::Menu; x++) {
            keyboardData.keyLastPressed[x] = false;
            keyboardData.keyPressed[x] = false;
        }

        // Reset mouse events
        for (int x = 0; x < MouseButton::RightButton; x++) {
            mouseData.buttonLastPressed[x] = false;
            mouseData.buttonPressed[x] = false;
        }
        mouseData.mousePos = {0,0};
    }

    void EventData::reload() {
        // Reset window events
        windowData.wasResized = false;
        windowData.wasMoved = false;

        // Reset keyboard events
        for (int x = 0; x < Key::Menu; x++) {
            keyboardData.keyLastPressed[x] = keyboardData.keyPressed[x];
        }
        for (int x = 0; x < keyboardData.charQueue.size(); x++) {
            keyboardData.charQueue.pop();
        }

        // Reset mouse events
        for (int x = 0; x < MouseButton::RightButton; x++) {
            mouseData.buttonLastPressed[x] = mouseData.buttonPressed[x];
        }
        mouseData.mouseLastPos = mouseData.mousePos;
        mouseData.mScrollH = 0.0f;
        mouseData.mScrollV = 0.0f;
    }
}