#include "time/Timer.hpp"

namespace arcana {
    Timer::Timer() {
        reset();
    }

    void Timer::reset() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    float Timer::getElapsed() {
        return getElapsedMillis() * 0.001f;
    }

    float Timer::getElapsedMillis() {
        return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - startTime).count() * 0.001f * 0.001f;
    }
}