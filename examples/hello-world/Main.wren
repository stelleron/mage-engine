import "mage-app" for MageApp, NativeApp, MageConfig
class Main is MageApp {
    construct new() {
        var config = MageConfig.new()
        super(config)
        System.print("Hello World")
        _x = 0
    }

    update(dt) {
        while (_x < 2000) {
            _x = _x + 1
            return false
        }
        return true
    }

    render() {

    }

    finish() {

    }
}