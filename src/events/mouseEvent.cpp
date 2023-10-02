#include "../include/events/mouseEvent.hpp"

using namespace Sdlk;

MouseEvent::MouseEvent(){
    _allEvents[MouseEventType::MOUSE_NO_EVENT] = true;
    for (int i = MouseEventType::MOUSE_BUTTON_DOWN; i <= MouseEventType::MOUSE_SCROLL_DOWN; i++) {
        _allEvents[static_cast<MouseEventType>(i)] = false;
    }
}

void MouseEvent::handlerMouseEvent(SDL_Event *event){
    switch(event->type){
        case SDL_MOUSEBUTTONDOWN:
            Mouse::setPosition(event);
            updateState(MouseEventType::MOUSE_BUTTON_DOWN, true);
            break;
        case SDL_MOUSEMOTION:
            Mouse::setPosition(event);
            updateState(MouseEventType::MOUSE_MOVE, true);
            break;
        default:
            break;
    }
}