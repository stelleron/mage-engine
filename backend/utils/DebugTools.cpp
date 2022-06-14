#include "spdlog/sinks/stdout_color_sinks.h"
#include "DebugTools.h"

namespace Mage {
    std::shared_ptr<spdlog::logger> DebugTools::EngineLog;
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
}