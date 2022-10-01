#include "utils/DebugTools.hpp"
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

// MAGE Engine application
class MageEngine : public Application{
    void config(AppConfig& config) {
        
    }
    void init(GameContext& ctx) {


    }
    void update(GameContext& ctx) {

    }
    void render(RenderContext& ctx) {

    }
    void finish() {
    
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
            
        }
    }

    // Build the game engine
    MageEngine engine;
    build(engine);
}