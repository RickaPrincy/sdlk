#ifndef __SDLK__
#define __SDLK__
    #include <iostream>
    #include <SDL2/SDL.h>

    #include "./utils.hpp"
    #include "./events/event.hpp"
    #include "./types/position.hpp"
    #include "./components/window.hpp"

    namespace Sdlk{
        class SDL{
            private:
                Uint32 _flags;
            public:
                void run();
                SDL(Uint32 flags);
                ~SDL();
        };
    }

#endif