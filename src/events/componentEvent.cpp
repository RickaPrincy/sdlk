#include "../include/events/componentEvent.hpp"

using namespace Sdlk;

ComponentEvent::ComponentEvent(){
    for (int i = ComponentEventType::CLICK; i <= ComponentEventType::HOVER; i++) {
        _allEvents[static_cast<ComponentEventType>(i)] = false;
    }
}