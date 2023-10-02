#ifndef _SDLK_MOUSE__
#define _SDLK_MOUSE__

    #include "SDL2/SDL.h"
    #include "../types/position.hpp"

    namespace Sdlk{
        class Mouse{
            public:
                static Position _position;
                static void setPosition(SDL_Event *event);
        };
    }
#endif