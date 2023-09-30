#ifndef __SDLK_POSITION__
#define __SDLK_POSITION__
    #include "./attribute.lib.hpp"

    namespace Sdlk{
        class Rgb;
        class Size;

        class Position{
            private:
                static const std::regex _format;
            public:
                int _x, _y;

                Position(int x ,int y):_x(x),_y(y){};
                Position(int xy):_x(xy),_y(xy){};
                Position(std::string input);
                Position():_x(0),_y(0){};

                Position& operator=(const Position& other);
                Position& operator=(const std::string& other);
                Position& operator=(const std::variant<Rgb,Size,Position,std::string> &other);

                static Position fromString(std::string input);
        };
    }
#endif