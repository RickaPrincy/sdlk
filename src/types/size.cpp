#include "../include/types/size.hpp"

using namespace Sdlk;

Size& Size::operator=(const Size& other) {
    if (this != &other) {
        _w = other._w;
        _h = other._h;
    }
    return *this;
}

