#include "../include/components/component.hpp"

using namespace Sdlk;

//----------------------------------------------------------------
Component::Component(){}
Component::Component(Style style):_style(style){}
Component::Component(StyleArg style){ _style.updateStyle(style); }
Component::~Component(){
    if(!Check::isNull(_texture)){
        Utils::clog("Destroy texture");
        SDL_DestroyTexture(_texture);
    }
}

//----------------------------------------------------------------
void Component::updateStyle(StyleArg style){ 
    Position temp = _style.getPosition();
    _style.updateStyle(style);

    if(temp._x != _style.getPosition()._x || temp._y != _style.getPosition()._y){
        for(const auto &child: _childrens){
            child->calcRealPosition();
        }
    }
}

void Component::updateStyle(Style style){ updateStyle(style.getAllStyles()); }
void Component::setTexture(SDL_Texture *texture){
    if(Check::isNull(_texture)){
        SDL_DestroyTexture(_texture);
    }
    _texture = texture;
}

void Component::appendChild(Component *child){ 
    if(child != this){
        child->_parent = this;
        _childrens.push_back(child); 
    }
}

//----------------------------------------------------------------
void  Component::render(SDL_Renderer *renderer){
    handlerEvent();
    
    if(Check::isNull(renderer)){
        Utils::cerr("Cannot render component without renderer");
        return;
    }

    if(Check::isNull(_texture)){
        Utils::cerr("Cannot render component without texture");
        return;
    }

    Utils::setRenderColor(renderer,_style.getColor());
    if(!Check::isNull(_parent)){
        Utils::setRenderTarget(renderer, _parent->_texture);
    }

    SDL_Rect rect = { 
        _style.getPosition()._x, 
        _style.getPosition()._y, 
        _style.getSize()._w, 
        _style.getSize()._h 
    };

    Utils::renderCopy(renderer,_texture,NULL,&rect);
    Utils::setRenderTarget(renderer,NULL);

    for(size_t i = 0; i < _childrens.size(); i++){
        _childrens.at(i)->render(renderer);
    }
}

Position Component::getRealPosition(){
    return _realPosition;
}

void Component::calcRealPosition(){
    _realPosition = Position(
        _parent->getRealPosition()._x + _style.getPosition()._x,
        _parent->getRealPosition()._y + _style.getPosition()._y
    );
}