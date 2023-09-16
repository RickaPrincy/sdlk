#include "../include/events/eventHandled.hpp"

using namespace Sdlk;

template <typename T>
void EventHandled<T>::updateState(T event, bool newState){
    _allEvents[event] = newState;
}

template <typename T>
bool EventHandled<T>::checkState(T event){
    return _allEvents[event];
}

template <typename T>
bool EventHandled<T>::hasOccured(T event){
    return checkState(event);
}

template <typename T>
bool EventHandled<T>::hasNotOccured(T event){
    return !checkState(event);
}