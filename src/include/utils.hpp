#ifndef __SDLK_UTILS__
#define __SDLK_UTILS__

    #include <iostream>
    #include <SDL2/SDL.h>

    namespace Sdlk{
        class Utils{
            public:
                static void cout(std::string message);
                static void cerr(std::string error);
                static void wait(Uint32 ms);
        };
    }

#endif