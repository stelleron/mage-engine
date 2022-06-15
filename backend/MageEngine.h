#ifndef MAGE_ENGINE_H
    #define MAGE_ENGINE_H
    // ===== Standard dependencies =====
    #include <string>
    // ===== Utility libraries =====
    #include "utils/Base.h"
    #include "utils/DebugTools.h"
    #include "utils/Color.h"
    #include "utils/MageConfig.h"
    // ===== Engine class =====
    namespace Mage {
        // Stores the game engine data
        class MageEngine {
            std::string resdir; // Directory to find resources
            public:
                MageEngine();
                ~MageEngine();
        };
    };
#endif