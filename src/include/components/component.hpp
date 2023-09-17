#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <SDL2/SDL.h>
    #include "../types/visibility.hpp"
    #include "../utils.hpp"

    namespace Sdlk{
        class Component{
            protected:
                Component *_parent = nullptr;
            public:
                SDL_Renderer *_renderer = nullptr;
                Component(Component *parent);
                ~Component();
        };
    }
#endif