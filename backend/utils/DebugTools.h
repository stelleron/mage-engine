#ifndef MAGE_DEBUGTOOLS_H
    #define MAGE_DEBUGTOOLS_H
    #include <memory>
    #include "spdlog/spdlog.h"

    #include "Base.h"
    namespace Mage {
        // Used to debug the game engine
        class MAGE_API DebugTools {
            private:   
                static std::shared_ptr<spdlog::logger> EngineLog;

                static int AllocationsMade;
                static int AllocationsFreed;
            public:
                static void Init();
                inline static std::shared_ptr<spdlog::logger>& GetLogger() {return EngineLog;}

                inline static void TrackAllocation() {AllocationsMade += 1;}
                inline static void TrackFree() {AllocationsFreed += 1;}

                static void Summarize();
        };
    }

    // Macros
    #ifdef DEBUG
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
    #endif
#endif