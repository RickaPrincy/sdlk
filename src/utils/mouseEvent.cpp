#include "../include/events/mouseEvent.hpp"

using namespace Sdlk;

MouseEvent::MouseEvent(){
    _allEvents[MouseEventType::MOUSE_NO_EVENT] = true;
    for (int i = MouseEventType::MOUSE_BUTTON_DOWN; i <= MouseEventType::MOUSE_SCROLL_DOWN; i++) {
        _allEvents[static_cast<MouseEventType>(i)] = false;
    }
}

void MouseEvent::updateEventState(MouseEventType event, bool newState){
    _allEvents[event] = newState;
}

bool MouseEvent::checkEventState(MouseEventType event){
    return _allEvents[event];
}

bool MouseEvent::isStateTrue(MouseEventType event){
    return checkEventState(event);
}

bool MouseEvent::isStateFalse(MouseEventType event){
    return !checkEventState(event);
}