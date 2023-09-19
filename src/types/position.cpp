#include "../include/types/position.hpp"

using namespace Sdlk;

Position& Position::operator=(const Position& other) {
    if (this != &other) {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}