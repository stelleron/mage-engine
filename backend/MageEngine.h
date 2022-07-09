#ifndef MAGE_ENGINE_H
    #define MAGE_ENGINE_H
    // ===== Standard dependencies =====
    #include <string>
    // ===== Utility libraries =====
    #include "utils/Base.h"
    #include "utils/DebugTools.h"
    #include "utils/Color.h"
    #include "utils/MageConfig.h"
    // ===== File libraries =====
    #include "files/FileSystem.h"
    // ===== Window libraries =====
    #include "window/MageWindow.h"
    // ===== Engine class =====
    namespace Mage {
        // Stores the game engine data
        class MageEngine {
            public:
                MageEngine(MageConfig* config);
                ~MageEngine();
        };
    };
#endif