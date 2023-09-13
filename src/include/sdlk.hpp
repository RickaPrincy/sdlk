#ifndef __SDLK__
#define __SDLK__

#include <iostream>
#include <SDL2/SDL.h>

#include "./utils.hpp"
namespace Sdlk{
    class SDL{
        private:
            Uint32 _flags;
        public:
            SDL(Uint32 flags);
            ~SDL();
    };
}

#endif