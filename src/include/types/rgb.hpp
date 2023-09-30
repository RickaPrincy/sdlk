#ifndef __SDLK_RGB__
#define __SDLK_RGB__

    #include "./attribute.lib.hpp"

    namespace Sdlk{
        class Position;
        class Size;

        class Rgb{
            private:
                static const std::regex _format;
            public:
                int _r = 0,_g = 0,_b = 0;
                Rgb(int r, int g, int b);
                Rgb(std::string input);
                Rgb(){};

                Rgb& operator=(const Rgb& other);
                Rgb& operator=(const std::string& other);
                Rgb& operator=(const std::variant<Rgb,Size,Position,std::string> &other);

                static Rgb fromString(std::string input);
        };
    }
#endif