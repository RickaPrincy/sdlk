#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::render(){
    if(Error<Component>::isNull(_parent)){
        //TODO : how if _renderer == nullptr | NULL?
        SDL_RenderPresent(_renderer);
    }
}

Component::Component(Component *parent): _parent(parent){
    if(!Error<Component>::isNull(_parent)){
        _renderer = parent->_renderer;
    }
}

Component::~Component(){
   Utils::cout("Destroy component");
}