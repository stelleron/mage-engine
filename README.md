# MAGE Engine - Making Awesome Games Easy with the Wren programming language!
The MAGE Engine is a 2D game engine built on top of the homemade Arcana2D framework(see [here](https://github.com/stelleron/arcana2d/tree/master)), and uses the incredibly simple and fast [Wren](https://wren.io/) programming language to expose the native C++ API. With a minimalist API that's easy to develop in, the MAGE Engine will help you Make Awesome Games Easy!

# Basic Template Program
```
// Sample import modules
import "mage-utils" for Vec2
import "mage-random" for Random
import "mage-timer" for Timer
import "mage-app" for AppConfig
import "mage-input" for Keyboard
import "mage-geom" for Point

// Main application template
class Main {
    construct new() {
        
    }
    config(cfg) {

    }
    init(ctx) {
        
    }
    update(ctx) {

    }
    render(ctx) {

    }
    finish() {
        
    }
}
```