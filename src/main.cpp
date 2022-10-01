#include "Arcana2D.hpp"
using namespace arcana;

class UntitledGame : public Application{
    Font font;
    void config(AppConfig& config) {
        config.width = 1024;
    }
    void init(GameContext& ctx) {
        font.load("cache/ThaleahFat.ttf");

    }
    void update(GameContext& ctx) {

    }
    void render(RenderContext& ctx) {
        ctx.print(font, "Hello World!");
    }
    void finish() {
    
    }
};

int main() {
    UntitledGame game;
    build(game);
}