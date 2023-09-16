#ifndef __SDLK_UTILS__
#define __SDLK_UTILS__

    #include <iostream>

    namespace Sdlk{
        class Utils{
            public:
                static void cout(std::string message);
                static void cerr(std::string error);
        };
    }

#endif