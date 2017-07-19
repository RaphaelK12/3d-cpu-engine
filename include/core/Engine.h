#ifndef ENGINE_CORE_ENGINE_H_
#define ENGINE_CORE_ENGINE_H_

#include "render/SDL2/SDL2Window.h"

/**
 * The core engine that runs the rendering.
 */
class Engine {
    private:
        bool isRunning;
        // float depthBuffer[];
        SDL2Window window;

    public:
        Engine();

    public:
        bool init();
        bool startRendering();
        bool stopRendering();

    private:
        bool renderOneFrame();
        void handleEvent(SDL_Event* sdlevent);
};


#endif // End header



