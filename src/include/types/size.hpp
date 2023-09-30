#ifndef __SDLK_SIZE__
#define __SDLK_SIZE__

    #include "./attribute.lib.hpp"

    namespace Sdlk{
        class Position;
        class Rgb;
        
        class Size{
            private:
                static const std::regex _format;
            public:
                int _w, _h;

                Size(int w, int h);
                Size(int wh);
                Size(std::string input);
                Size():_w(10),_h(10){};

                Size& operator=(const Size& other);
                Size& operator=(const std::string& other);
                Size& operator=(const std::variant<Rgb,Size,Position,std::string> &other);

                static Size fromString(std::string input);
        };
    }
#endif