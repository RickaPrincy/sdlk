#ifndef __SDLK_SIZE__
#define __SDLK_SIZE__
    #include <iostream>

    namespace Sdlk{
        class Size{
            public:
                int _w, _h;
                Size(int w, int h):_w(w), _h(h){};
                Size(int wh):_w(wh),_h(wh){};
                Size():_w(0),_h(0){};
                Size& operator=(const Size& other);
        };
    }
#endif