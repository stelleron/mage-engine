class Main {
    construct new() {
        System.print("Hello World")
    }

    #!main_func = "update"
    update(dt) {
        System.print(dt)
        return true
    }

    #!main_func = "render"
    render() {

    }

    #!main_func = "finish"
    finish() {

    }
}