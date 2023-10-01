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

                Position();
                Position(int x ,int y);
                Position(int xy);
                Position(std::string input);

                Position& operator=(const Position& other);
                Position& operator=(const std::string& other);
                Position& operator=(const std::variant<Rgb,Size,Position,std::string> &other);

                static Position fromString(std::string input);
        };
    }
#endif