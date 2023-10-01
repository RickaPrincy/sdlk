#include "../include/events/mouseEvent.hpp"

using namespace Sdlk;

MouseEvent::MouseEvent(){
    _allEvents[MouseEventType::MOUSE_NO_EVENT] = true;
    for (int i = MouseEventType::MOUSE_BUTTON_DOWN; i <= MouseEventType::MOUSE_SCROLL_DOWN; i++) {
        _allEvents[static_cast<MouseEventType>(i)] = false;
    }
}

void MouseEvent::handlerMouseEvent(SDL_Event *event){
    resetAll();
    Utils::clog("Resized made");
}