#ifndef _SDLK_MOUSE__
#define _SDLK_MOUSE__

    #include "../types/position.hpp"
    #include "SDL2/SDL.h"

    namespace Sdlk{
        class Mouse{
            public:
                static Position _position;
                static void takePosition(SDL_Event *event);
        };
    }
#endif