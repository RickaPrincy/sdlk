#include "../include/types/rgb.hpp"

using namespace Sdlk;

Rgb::Rgb(int r, int g, int b){
    if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0){
        std::cerr << "Rgb value not valid (min : 0, max : 255)" << std::endl;
        return;
    }
    _r = r;
    _g = g;
    _b = b;
}

Rgb& Rgb::operator=(const Rgb& other) {
    if (this != &other) {
        _r = other._r;
        _g = other._g;
        _b = other._b;
    }
    return *this;
}