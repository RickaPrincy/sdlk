#ifndef __SDLK_APP__
#define __SDLK_APP__

    #include <iostream>
    #include <string>

    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
    #include <SDL2/SDL_ttf.h>

    #include "./utils/program.hpp"
    #include "./utils/utils.hpp"
    #include "./utils/check.hpp"
    #include "./types/size.hpp"
    #include "./types/position.hpp"
    #include "./types/rgb.hpp"
    #include "./events/event.hpp"
    #include "./events/eventHandled.hpp"
    #include "./events/mouseEvent.hpp"
    #include "./events/windowEvent.hpp"
    #include "./components/component.hpp"
    #include "./components/window.hpp"

    namespace Sdlk{
        class App{
            public:
                Window *_window = nullptr;
                Event _event;
                void run();
                void initSdl(Uint32 flags);
                void quitSdl(Uint32 flags);
                App(
                    std::string title, 
                    Size size,
                    Position position = Position(SDL_WINDOWPOS_CENTERED),
                    Uint32 flags = SDL_INIT_EVERYTHING 
                );
                ~App();
        };
    }
#endif