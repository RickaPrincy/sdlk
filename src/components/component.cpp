#include "../include/components/component.hpp"

using namespace Sdlk;

Component::Component(Component *parent): _parent(parent){
    if(parent != nullptr || parent != NULL){
        _renderer = parent->_renderer;
    }
}

Component::~Component(){
    if(_renderer != nullptr){
        SDL_DestroyRenderer(_renderer);
    }
}