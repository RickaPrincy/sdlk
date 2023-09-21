#ifndef __SDLK_TYPES__
#define __SDLK_TYPES__

    #include <iostream>

    namespace Sdlk{
        class Position{
            public:
                int _x, _y;
                Position(int x ,int y):_x(x),_y(y){};
                Position(int wh):_x(wh),_y(wh){};
                Position():_x(0),_y(0){};
                Position& operator=(const Position& other);
        };
    }
#endif