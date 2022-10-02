#include "utils/DebugTools.hpp"
#include "wren/Frontend.hpp"
#include "Arcana2D.hpp"
#include "wren.hpp"
#include <string>

using namespace arcana;
using namespace mage;

// Logging callbacks
void MageLogCallback(const char* message) {
    MAGE_INFO(message);
}

void MageErrorCallback(const char* message) {
    MAGE_ERROR(message);
}

// Frontend 
Frontend frontend;

// MAGE Engine application
class MageEngine : public Application{
    void config(AppConfig& config) {
        frontend.uData.config = &config;
        wrenEnsureSlots(frontend.vm, 2);
        wrenSetSlotHandle(frontend.vm, 0, frontend.app.mainInstance);
        wrenSetSlotHandle(frontend.vm, 1, frontend.app.configInstance);
        wrenCall(frontend.vm, frontend.app.configFunc);
    }
    void init(GameContext& ctx) {
        frontend.uData.game_ctx = &ctx;
        wrenEnsureSlots(frontend.vm, 2);
        wrenSetSlotHandle(frontend.vm, 0, frontend.app.mainInstance);
        wrenSetSlotHandle(frontend.vm, 1, frontend.app.gameCtxInstance);
        wrenCall(frontend.vm, frontend.app.initFunc);
    }
    void update(GameContext& ctx) {
        frontend.uData.game_ctx = &ctx;
        wrenEnsureSlots(frontend.vm, 2);
        wrenSetSlotHandle(frontend.vm, 0, frontend.app.mainInstance);
        wrenSetSlotHandle(frontend.vm, 1, frontend.app.gameCtxInstance);
        wrenCall(frontend.vm, frontend.app.updateFunc);
    }
    void render(RenderContext& ctx) {
        frontend.uData.render_ctx = &ctx;
        wrenEnsureSlots(frontend.vm, 2);
        wrenSetSlotHandle(frontend.vm, 0, frontend.app.mainInstance);
        wrenSetSlotHandle(frontend.vm, 1, frontend.app.renderCtxInstance);
        wrenCall(frontend.vm, frontend.app.renderFunc);
    }
    void finish() {
        wrenEnsureSlots(frontend.vm, 1);
        wrenSetSlotHandle(frontend.vm, 0, frontend.app.mainInstance);
        wrenCall(frontend.vm, frontend.app.finishFunc);
    }
};

int main(int argc, char** argv) {
    // Initialise DebugTools
    DebugTools::Init();

    // Set callbacks
    logger.setLogCallback(MageLogCallback);
    logger.setErrorCallback(MageErrorCallback);

    // Now check the file path for a MAGE project
    if (argc > 2) {
        MAGE_ERROR("Error: Too many arguments!");
    }
    else if (argc < 2) {
        MAGE_ERROR("Error: Too few arguments!");
    }
    else {
        std::string filepath = argv[1];
        filepath += "main.wren";
        if (!arcana::filesystem::fileExists(filepath)) {
            MAGE_ERROR("Error: main.wren does not exist in the given directory!");
        }
        else {
            // Start the frontend
            filepath = argv[1];
            frontend.start(filepath);
            // Build the game engine
            MageEngine engine;
            build(engine);
        }
    }
}