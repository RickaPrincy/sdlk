#include "../include/components/component.hpp"

using namespace Sdlk;

//----------------------------------------------------------------
void Component::resetAllEvent(){ 
    _events.resetAll(); 

    for(size_t i = 0; i < _childrens.size(); i++){
        _childrens.at(i)->resetAllEvent();
    }
}

//----------------------------------------------------------------
void Component::onClick(const std::function<void()> &onClickFunction){
    _actions.insert_or_assign(ComponentEventType::CLICK, onClickFunction);
}

void Component::onHover(const std::function<void()> &onHoverFunction){
    _actions.insert_or_assign(ComponentEventType::HOVER, onHoverFunction);
}

//----------------------------------------------------------------
void Component::shouldExecuteEvent(ComponentEventType event){
    if(
        _actions.find(event) != _actions.end()
        && _events.hasOccured(event)
    ){
        _actions.at(event)();
    }
}

void Component::executeEventActions(){
    shouldExecuteEvent(ComponentEventType::HOVER);
    shouldExecuteEvent(ComponentEventType::CLICK);
}