#include "../include/types/Rgb.hpp"

using namespace Sdlk;

Rgb::Rgb(int r, int g, int b){
    if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0){
        Utils::cerr("Rgb value not valid (min : 0, max : 255)");
        return;
    }
    _r = r;
    _g = g;
    _b = b;
}