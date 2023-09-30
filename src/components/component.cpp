#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::appendChild(Component *child){ 
    if(child != this){
        child->_parent = this;
        _childrens.push_back(child); 
    }
}

StyleVariant Component::getStyle(Attribute key){
    return _style.getStyle(key);
}

void Component::updateStyle(StyleArg style){
    _style.updateStyle(style);
}

void Component::setTexture(SDL_Texture *texture){
    if(Check::isNull(_texture)){
        SDL_DestroyTexture(_texture);
    }
    _texture = texture;
}

void  Component::render(SDL_Renderer *renderer){
    Rgb color;
    Size size;
    Position position;

    color = _style.getStyle(Attribute::COLOR);
    size = _style.getStyle(Attribute::SIZE);
    position = _style.getStyle(Attribute::POSITION);

    if(Check::isNull(renderer)){
        Utils::cerr("Cannot render component without renderer");
        return;
    }

    if(Check::isNull(_texture)){
        Utils::cerr("Cannot render component without texture");
        return;
    }

    Utils::setRenderColor(renderer,color);
    if(!Check::isNull(_parent)){
        Utils::setRenderTarget(renderer, _parent->_texture);
    }

    SDL_Rect rect = { position._x, position._y, size._w, size._h };
    Utils::renderCopy(renderer,_texture,NULL,&rect);
    Utils::setRenderTarget(renderer,NULL);
    for(size_t i = 0; i < _childrens.size(); i++){
        _childrens.at(i)->render(renderer);
    }
}

Component::Component(StyleArg style){
    _style.updateStyle(style);
}

Component::~Component(){
    if(!Check::isNull(_texture)){
        Utils::clog("Destroy texture");
        SDL_DestroyTexture(_texture);
    }
}