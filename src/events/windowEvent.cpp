#include "../include/events/windowEvent.hpp"
using namespace Sdlk;

WindowEvent::WindowEvent(){
    _allEvents[WindowEventType::WINDOW_SHOWN] = true;
    for (int i = WindowEventType::WINDOW_HIDDEN; i <= WindowEventType::WINDOW_CLOSE; i++) {
        _allEvents[static_cast<WindowEventType>(i)] = false;
    }
}

void WindowEvent::handlerWindowEvent(SDL_Event *event){
    resetAll();
    switch(event->window.event){
        case SDL_WINDOWEVENT_RESIZED:
            updateState(WindowEventType::WINDOW_RESIZED, true);
            break;
        default:
            break;
    }
}