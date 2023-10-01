#include "../include/components/component.hpp"

using namespace Sdlk;

//----------------------------------------------------------------
void Component::onClick(const std::function<void()> &onClickFunction){
    _onClickFunction = onClickFunction;
}

//----------------------------------------------------------------
void Component::handlerEvent(){
    if(_onClickFunction && Event::_mouseEvents.hasOccured(MouseEventType::MOUSE_BUTTON_DOWN)){
        if (
            Mouse::_position._x >= _realPosition._x 
            && Mouse::_position._x <= (_realPosition._x + _style.getSize()._w) 
            && Mouse::_position._y >= _realPosition._y
            && Mouse::_position._y  <= (_realPosition._y + _style.getSize()._h)
        ) {
            _onClickFunction();
        }
    }
}