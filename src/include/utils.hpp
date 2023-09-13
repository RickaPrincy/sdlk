#ifndef __SDLK_ERROR_
#define __SDLK_ERROR__

#include <iostream>

namespace Sdlk{
    class Utils{
        public:
            static void cout(std::string message);
            static void cerr(std::string error);
    };
}

#endif