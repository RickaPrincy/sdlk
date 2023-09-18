#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <SDL2/SDL.h>
    #include "../types/visibility.hpp"
    #include "../utils.hpp"
    #include "../error.hpp"

    namespace Sdlk{
        class Component{
            protected:
                Component *_parent = nullptr;
                SDL_Renderer *_renderer = nullptr;
            public:
                void render();
                Component(Component *parent);
                ~Component();
        };
    }
#endif