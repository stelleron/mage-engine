#ifndef MAGE_TIMER_HPP
    #define MAGE_TIMER_HPP
    #include <chrono>
    namespace Mage {
        // Used to create a timer object
        class Timer {
            private:
                std::chrono::time_point<std::chrono::high_resolution_clock> currTime;
            public:
                Timer();

                void setNow(); // Set the timer to the current time
                float elapsed(); // Get the elapsed time
                float elapsedMilli(); // Get the elapsed time in milliseconds
        };
    }
#endif 
