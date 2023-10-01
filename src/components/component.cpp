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
void Component::updateStyle(StyleArg style){ _style.updateStyle(style);}
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

//----------------------------------------------------------------
void Component::onClick(const std::function<void()> &onClickFunction){
    _onClickFunction = onClickFunction;
}

//----------------------------------------------------------------
void Component::handlerEvent(){
    if(Event::_mouseEvents.hasOccured(MouseEventType::MOUSE_BUTTON_DOWN)){
        if(_onClickFunction){
            _onClickFunction();
        }
    }
}