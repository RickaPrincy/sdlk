#include "../include/components/component.hpp"

using namespace Sdlk;

//----------------------------------------------------------------
void Component::handlerHover(){
    if(
        Mouse::_position._x >= _realPosition._x 
        && Mouse::_position._x <= (_realPosition._x + _style.getSize()._w) 
        && Mouse::_position._y >= _realPosition._y
        && Mouse::_position._y  <= (_realPosition._y + _style.getSize()._h)
    ){
        _events.updateState(ComponentEventType::HOVER,true);
    }
}

//----------------------------------------------------------------
void Component::handlerClick(){
    if(
        _events.hasOccured(ComponentEventType::HOVER)
        && Event::_mouseEvents.hasOccured(MouseEventType::MOUSE_BUTTON_DOWN)
    ){
        _events.updateState(ComponentEventType::CLICK,true);
    }
}

//----------------------------------------------------------------
void Component::handlerAllEvent(){
    handlerHover();
    handlerClick();

    for(size_t i = 0; i < _childrens.size(); i++){
        _childrens.at(i)->handlerAllEvent();
    }

    executeEventActions();
}