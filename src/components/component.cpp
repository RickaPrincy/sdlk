#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::setSize(Size size){ _size = size; }
void Component::setColor(Rgb color){ _color = color; }
void Component::setPosition(Position position){ _position = position; }

void Component::appendChild(Component *child){ 
    if(child != this){
        child->_parent = this;
        _childrens.push_back(child); 
    }
}

void Component::setTexture(SDL_Texture *texture){
    if(Check::isNull(_texture)){
        SDL_DestroyTexture(_texture);
    }
    _texture = texture;
}

void  Component::render(SDL_Renderer *renderer){
    if(Check::isNull(renderer)){
        Utils::cerr("Cannot render component without renderer");
        return;
    }

    if(Check::isNull(_texture)){
        Utils::cerr("Cannot render component without texture");
        return;
    }

    Utils::setRenderColor(renderer,_color);
    if(!Check::isNull(_parent)){
        Utils::setRenderTarget(renderer, _parent->_texture);
    }

    SDL_Rect rect = { _position._x, _position._y, _size._w, _size._h };
    Utils::renderCopy(renderer,_texture,NULL,&rect);
    Utils::setRenderTarget(renderer,NULL);
    for(size_t i = 0; i < _childrens.size(); i++){
        _childrens.at(i)->render(renderer);
    }
}

Component::Component(Size size, Position position)
:_size(size), _position(position){
    //empty for the moment
}

Component::~Component(){
    if(!Check::isNull(_texture)){
        Utils::clog("Destroy texture");
        SDL_DestroyTexture(_texture);
    }
}