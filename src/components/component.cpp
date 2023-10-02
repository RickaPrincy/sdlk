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
    _style.updateStyle(style);

    if(style.find(Attribute::POSITION) != style.end()){
        calcRealPosition();
    }
    if(style.find(Attribute::SIZE) != style.end()){
        setTexture(nullptr);
    }

    makeRenderer();
}

void Component::updateStyle(Style style){ updateStyle(style.getAllStyles()); }
void Component::setTexture(SDL_Texture *texture){
    if(!Check::isNull(_texture)){
        SDL_DestroyTexture(_texture);
    }
    _texture = texture;
}

void Component::appendChilds(std::vector<Component*> childs){
    for(auto *child: childs){
        appendChild(child);
    }
}

void Component::appendChild(Component *child){ 
    if(child != this){
        child->_parent = this;
        child->calcRealPosition();
        _childrens.push_back(child); 
    }
}

//----------------------------------------------------------------
void Component::makeRenderer(){
    _shouldRenderer = true;
    if(!Check::isNull(_parent)){
        _parent->makeRenderer();
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

    if(_shouldRenderer){
        for(size_t i = 0; i < _childrens.size(); i++){
            _childrens.at(i)->render(renderer);
        }
    }

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


    if(_actions.find(ComponentEventType::RENDER) != _actions.end()){
        _actions.at(ComponentEventType::RENDER)();
    }
    
    _shouldRenderer = false;
}

Position Component::getRealPosition(){
    return _realPosition;
}

void Component::calcRealPosition(){
    if(!Check::isNull(_parent)){
        _realPosition = Position(
            _parent->getRealPosition()._x + _style.getPosition()._x,
            _parent->getRealPosition()._y + _style.getPosition()._y
        );
    }
    else{
        _realPosition = Position(
            _style.getPosition()._x,
            _style.getPosition()._y
        );
    }

    for(const auto &child: _childrens){
        child->calcRealPosition();
    }
}