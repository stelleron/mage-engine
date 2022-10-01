#include "spdlog/sinks/stdout_color_sinks.h"
#include "utils/DebugTools.hpp"

namespace mage {
    std::shared_ptr<spdlog::logger> DebugTools::EngineLog;
    arcana::Timer DebugTools::debugTimer;
    int DebugTools::AllocationsMade;
    int DebugTools::AllocationsFreed;

    void DebugTools::Init()
    {
        spdlog::set_pattern("%^%v%$");
        EngineLog = spdlog::stdout_color_mt("ENGINELOG");
        EngineLog->set_level(spdlog::level::trace);
    }

    void DebugTools::Summarize() {
        MAGE_INFO("Summary: {0} allocations tracked, {1} freed and {2} unfreed.", 
                 AllocationsMade, AllocationsFreed, AllocationsMade - AllocationsFreed);
    }
    
    void DebugTools::StartTimer() {
        debugTimer.reset();
    }

    void DebugTools::EndTimer() {
        MAGE_INFO("Debug: Time taken to run the given code was {0}ms", debugTimer.getElapsedMillis());
    }
}