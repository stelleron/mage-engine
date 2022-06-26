class Main {
    construct new() {
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