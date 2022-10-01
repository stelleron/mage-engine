#ifndef MAGE_DEBUGTOOLS_HPP
    #define MAGE_DEBUGTOOLS_HPP
    #ifdef DEBUG
        #include "time/Timer.hpp"
        #include <memory>
        #include "spdlog/spdlog.h"
        namespace mage {
            // Used to debug the game engine
            class DebugTools {
                private:   
                    static std::shared_ptr<spdlog::logger> EngineLog;
                    static arcana::Timer debugTimer;
                    static int AllocationsMade;
                    static int AllocationsFreed;
                public:
                    static void Init();
                    inline static std::shared_ptr<spdlog::logger>& GetLogger() {return EngineLog;}

                    inline static void TrackAllocation() {AllocationsMade += 1;}
                    inline static void TrackFree() {AllocationsFreed += 1;}

                    static void StartTimer();
                    static void EndTimer();

                    static void Summarize();
            };
        }

        // Macros

        // Logger macros
        #define MAGE_INFO(...) DebugTools::GetLogger()->info(__VA_ARGS__)
        #define MAGE_WARN(...) DebugTools::GetLogger()->warn(__VA_ARGS__)
        #define MAGE_TRACE(...) DebugTools::GetLogger()->trace(__VA_ARGS__)
        #define MAGE_ERROR(...) DebugTools::GetLogger()->error(__VA_ARGS__)
        #define MAGE_OUTPUT(arg) MAGE_INFO("{0}", arg)
        // Custom allocators
        #define MAGE_ALLOC(arg) new arg; DebugTools::TrackAllocation()
        #define MAGE_ALLOC_ARRAY(arg, size) new arg[size]; DebugTools::TrackAllocation()
        #define MAGE_FREE(arg) delete arg; DebugTools::TrackFree()
        #define MAGE_FREE_ARRAY(arg) delete[] arg; DebugTools::TrackFree()
        // Timing functions
        #define START_TIME() DebugTools::StartTimer()
        #define END_TIME() DebugTools::EndTimer()
    #else
        #define MAGE_INFO(...)
        #define MAGE_WARN(...)
        #define MAGE_TRACE(...)
        #define MAGE_ERROR(...)
        #define MAGE_OUTPUT(...)

        #define MAGE_ALLOC(arg) new arg;
        #define MAGE_ALLOC_ARRAY(arg, size) new arg[size];
        #define MAGE_FREE(arg) delete arg;
        #define MAGE_FREE_ARRAY(arg) delete[] arg;

        #define START_TIME()
        #define END_TIME()
    #endif
#endif