#ifndef __SDLK_RGB__
#define __SDLK_RGB__
    #include <iostream>
    #include "../utils.hpp"

    namespace Sdlk{
        class Rgb{
            public:
                int _r = 0,_g = 0,_b = 0;
                Rgb(int r, int g, int b);
                Rgb(){};
        };
    }
#endif