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
# Usage
The MAGE Engine has currently only been tested on MacOS, and ports for Windows and Linux will be rolled out eventually. Right now, the MAGE Engine can be downloaded as a ZIP file or cloned from GitHub, then compiled with Premake or GNU Make. From there, you can start writing a game in Wren externally, putting all of the required files and resources within a single directory that contains a `main.wren` entry point. This folder can then be dropped on the compiled MAGE executable and run.

# Modules
- `mage-utils`: Provides Vector and Color classes
- `mage-random`: Provides random number generation
- `mage-window`: Provides access to window manipulation and event handling
- `mage-timer`: Provides a timer class for processing and handling time
- `mage-res`: For loading files, images and fonts
- `mage-camera`: Allows access to the scene camera and setting zoom, rotation and offset
- `mage-input`: For receiving inputs from the keyboard and mouse
- `mage-geom`: Provides simple classes for defining shapes
- `mage-gfx`: For rendering graphics and creating shader programs
- `mage-audio`: Simple audio playing and management

