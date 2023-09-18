#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::setColor(Rgb color){
    if(SDL_SetRenderDrawColor(_renderer,color._r, color._g, color._b, 255) != 0){
        Utils::cerr("Changing color error");
    }
    _color._r = color._r;
    _color._g = color._g;
    _color._b = color._b;
}

void Component::render(){
    setColor(_color);

    if(Error<Component>::isNull(_parent)){
        //TODO : how if _renderer == nullptr | NULL?

        if(SDL_RenderClear(_renderer) != 0){
            Utils::cerr("Error to clean renderer");
        }
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