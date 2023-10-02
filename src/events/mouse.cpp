#include "../include/utils/utils.hpp"
#include "../include/events/mouse.hpp"

using namespace Sdlk;
Position Mouse::_position;

void Mouse::setPosition(SDL_Event *event){
    Mouse::_position._x = event->button.x;
    Mouse::_position._y = event->button.y;
}