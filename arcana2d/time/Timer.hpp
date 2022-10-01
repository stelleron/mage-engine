#ifndef ARCANA2D_TIMER
    #define ARCANA2D_TIMER
    #include <chrono>

    namespace arcana {
        using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
        // Used to create a timer object
        class Timer {
            private:
                TimePoint startTime;
            public:
                // Constructor
                Timer();

                // Reset the timer
                void reset();

                // Get the elapsed time
                float getElapsed();

                // Get the elapsed time in milliseconds
                float getElapsedMillis();
        };
    }
#endif