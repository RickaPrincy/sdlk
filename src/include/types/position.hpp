#ifndef __SDLK_TYPES__
#define __SDLK_TYPES__

    #include <iostream>

    namespace Sdlk{
        class Position{
            public:
                int _x, _y;
                Position(int x ,int y):_x(x),_y(y){};
                Position():_x(0),_y(0){};
                Position& operator=(const Position& other);
                    if (this != &other) {  // Vérifiez si vous n'êtes pas en train de vous assigner à vous-même
                        _x = other._x;
                        _y = other._y;
                    }
                    return *this;  // Retourne une référence sur l'objet actuel
                }
        };
    }
#endif