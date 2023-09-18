#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::render(){
    if(_parent == nullptr || _parent == NULL){
        //TODO : how if _renderer == nullptr | NULL?
        SDL_RenderPresent(_renderer);
    }
}

Component::Component(Component *parent): _parent(parent){
    if(parent != nullptr || parent != NULL){
        _renderer = parent->_renderer;
    }
}

Component::~Component(){
   Utils::cout("Destroy component");
}