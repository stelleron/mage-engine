import "mage-utils" for Vec2, Color
import "mage-random" for Random
import "mage-app" for AppConfig

class Main {
    construct new() {

    }
    config(cfg) {
        cfg.title = "MAGE Engine - A 2D Game Engine for Making Awesome Games Easy"
        cfg.background_color = Color.new(50, 50, 50, 255)
        cfg.resizable = true
    }
    init(ctx) {
        System.print(Random.generate(2, 3))
    }
    update(ctx) {

    }
    render(ctx) {

    }
    finish() {
        
    }
}

