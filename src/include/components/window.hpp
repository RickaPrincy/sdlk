#ifndef __SDLK_WINDOW__
#define __SDLK_WINDOW__

    #include <SDL2/SDL.h>
    #include <iostream>
    #include <string>
    #include "../utils/program.hpp"
    #include "../utils/check.hpp"
    #include "../utils/utils.hpp"
    #include "../types/rgb.hpp"
    #include "../types/position.hpp"
    #include "../types/size.hpp"
    #include "./component.hpp"
    #include "./box.hpp"

    namespace Sdlk{
        class Window{
            public:
                Box _box;
                SDL_Renderer *_renderer = nullptr;
                SDL_Window *_sdl_window = nullptr;
                void render();
                Window(
                    std::string title, 
                    Size size,
                    Position position = Position(SDL_WINDOWPOS_CENTERED),
                    Uint32 flags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
                );
                ~Window();
        };
    }
#endif