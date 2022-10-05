// Sample import modules
import "mage-utils" for Vec2, Color
import "mage-geom" for Circle
import "mage-gfx" for Texture
import "mage-random" for Random
import "mage-timer" for Timer
import "mage-app" for AppConfig
import "mage-input" for Keyboard
import "mage-geom" for Point

// Main application template
class Main {
    construct new() {
        _circle = Circle.new(Vec2.new(50, 50), 40)
    }
    config(cfg) {

    }
    init(ctx) {

    }
    update(ctx) {

    }
    render(ctx) {
        ctx.drawCircle(_circle, Color.new(255, 0, 0, 255), 1)
    }
    finish() {
        
    }
}

