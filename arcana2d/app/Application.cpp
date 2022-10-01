#include "utils/Logger.hpp"
#include "time/Timer.hpp"
#include "app/Application.hpp"
#include "gfx/Shader.hpp"

#include <thread>

namespace arcana {
    void build(Application& app) {
        LOG("Arcana2D: Building the application!");

        // Variable declarations
        AppConfig config;
        GameContext gameCtx;
        RenderContext renderCtx;
        Timer internalClock;
        float deltatimeCap; // Used for capping frame speed
        Window window;
        Camera camera;
        Shader shader;

        // Game Loop
        // 1. INIT
        // First have the user modify the app config
        LOG("Arcana2D: Configuring the application!");
        app.config(config);

        // And then initialise the application
        deltatimeCap = 1.0f/config.fps_cap;
        window.init(config);
        camera.dimensions = Vector2(config.width, config.height);
        gameCtx.window.set(window);
        gameCtx.camera.set(camera);
        window.setData(&gameCtx);
        LOG("Arcana2D: Initialising the application!");
        app.init(gameCtx);

        renderCtx.init();
        shader.load(0, 0);

        // 2. UPDATE
        LOG("Arcana2D: Starting game loop!");
        do {
            gameCtx.events.reload();
            window.pollEvents();

            if (window.isActive()) {
                // Update
                gameCtx.camera.set(camera);
                internalClock.reset();
                app.update(gameCtx);

                // Render
                window.fill();
                renderCtx.setCurrentCamera(*gameCtx.camera.get());
                renderCtx.setCurrentShader(shader);
                app.render(renderCtx);
                renderCtx.drawBatch();
                window.swapBuffer();

                // End loop
                // Put thread to sleep to cap framerate
                if (internalClock.getElapsed() < deltatimeCap) {
                    float sleepTime = deltatimeCap - internalClock.getElapsed();
                    std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long int>(sleepTime * 1000.0f)));
                }

                gameCtx.timer.set(internalClock.getElapsed());
            }

        } while(!window.shouldClose());

        // 3. FINISH
        LOG("Arcana2D: Disposing the application!");
        app.finish();
    }
}