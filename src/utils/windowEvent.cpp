#include "../include/events/windowEvent.hpp"

using namespace Sdlk;

WindowEvent::WindowEvent(){
    _allEvents[WindowEventType::WINDOW_SHOWN] = true;
    for (int i = WindowEventType::WINDOW_HIDDEN; i <= WindowEventType::WINDOW_CLOSE; i++) {
        _allEvents[static_cast<WindowEventType>(i)] = false;
    }
}

void WindowEvent::updateEventState(WindowEventType event, bool newState){
    _allEvents[event] = newState;
}

bool WindowEvent::checkEventState(WindowEventType event){
    return _allEvents[event];
}

bool WindowEvent::isStateTrue(WindowEventType event){
    return checkEventState(event);
}

bool WindowEvent::isStateFalse(WindowEventType event){
    return !checkEventState(event);
}