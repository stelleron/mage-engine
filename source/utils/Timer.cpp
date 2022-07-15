#include "utils/Timer.hpp"
namespace Mage {
    Timer::Timer() {
        setNow();
    }

    void Timer::setNow() {
        currTime = std::chrono::high_resolution_clock::now();
    }

    float Timer::elapsed() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - currTime).count() * 0.001f * 0.001f * 0.001f;
    }

    float Timer::elapsedMilli() {
        return elapsed() * 1000.0f;
    }
}