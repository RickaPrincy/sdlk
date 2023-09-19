#ifndef __SDLK__
#define __SDLK__
    #include <iostream>
    #include <SDL2/SDL.h>

    #include "./utils.hpp"
    #include "./program.hpp"
    #include "./error.hpp"
    #include "./types/visibility.hpp"
    #include "./types/rgb.hpp"
    #include "./types/size.hpp"
    #include "./types/position.hpp"
    #include "./events/eventHandled.hpp"
    #include "./events/mouseEvent.hpp"
    #include "./events/windowEvent.hpp"
    #include "./events/event.hpp"
    #include "./components/component.hpp"
    #include "./components/window.hpp"
    

    namespace Sdlk{
        class App{
            public:
                Event _event;
                Window *_window = nullptr;
                void initSdl(Uint32 flags);
                void run();

                App(
                    std::string name, Size size,
                    Position position = Position(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 
                    Uint32 flags = SDL_INIT_EVERYTHING
                );
                ~App();
        };
    }

#endif