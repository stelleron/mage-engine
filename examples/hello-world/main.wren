import "mage-utils" for Vec2, Color
import "mage-random" for Random
import "mage-timer" for Timer
import "mage-app" for AppConfig
import "mage-input" for Keyboard
import "mage-geom" for Point

class Main {
    construct new() {
        _point = Point.new(40, 40)
    }
    config(cfg) {
        cfg.title = "MAGE Engine - A 2D Game Engine for Making Awesome Games Easy"
        cfg.resizable = true
    }
    init(ctx) {
        _point.pos = Vec2.new(40, 50)
    }
    update(ctx) {

    }
    render(ctx) {

    }
    finish() {
        
    }
}

