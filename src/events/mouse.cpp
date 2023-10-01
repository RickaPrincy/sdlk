#include "../include/events/mouse.hpp"

Position Mouse::_position;
using namespace Sdlk;

void Mouse::takePosition(SDL_Event *event){
    Mouse::_position._x = event->button.x;
    Mouse::_position._y = event->button.y;
}