#include "../include/events/windowEvent.hpp"

using namespace Sdlk;

WindowEvent::WindowEvent(){
    _allEvents[WindowEventType::WINDOW_SHOWN] = true;
    for (int i = WindowEventType::WINDOW_HIDDEN; i <= WindowEventType::WINDOW_CLOSE; i++) {
        _allEvents[static_cast<WindowEventType>(i)] = false;
    }
}