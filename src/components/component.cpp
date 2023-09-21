#include "../include/components/component.hpp"

using namespace Sdlk;

void Component::setColor(Rgb color){
    if(SDL_SetRenderDrawColor(_renderer,color._r, color._g, color._b, 255) != 0){
        Utils::cerr("Changing color error");
    }
    _color = color;
}

void Component::releaseRenderer(SDL_Renderer *renderer){
    if(SDL_SetRenderTarget(renderer, NULL) != 0){
        Program::exit(EXIT_FAILURE,"Error when try to release a renderer");
    }
}

void Component::clearRenderer(SDL_Renderer *renderer){
    if(SDL_RenderClear(renderer) != 0){
        Program::exit(EXIT_FAILURE,"Error when try to clear a renderer");
    }
}

void Component::render(){
    this->setColor(_color);
    if(Error<Component>::isNull(_parent)){
        //TODO : how if _renderer == nullptr | NULL?

        if(SDL_RenderClear(_renderer) != 0){
            Utils::cerr("Error to clean renderer");
        }
        SDL_RenderPresent(_renderer);
    }
    else{
        if(Error<SDL_Texture>::isNull(_texture)){
            _texture = SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size._w,_size._h);
            if (Error<SDL_Texture>::isNull(_texture,"Cannot create the texture")){
                Program::exit(EXIT_FAILURE);
                return;
            }  

            this->setRenderToMe();
            this->setColor(_color);
            Component::clearRenderer(_renderer);
            Component::releaseRenderer(_renderer);
        }

        if(!Error<Component>::isNull(_parent) || !Error<Component>::isNull(_parent->_parent)){
            _parent->setRenderToMe();
        }

        SDL_Rect rect = {_position._x, _position._y, _size._w, _size._h};
        if(SDL_RenderCopy(_renderer,_texture, NULL, &rect) != 0){
            Program::exit(EXIT_FAILURE,"Error to copy the texture to an renderer target as texture");
            return;
        }

        Component::releaseRenderer(_renderer);
    }

    if(_childrens.size() > 0){
        for(size_t i = 0; i < _childrens.size(); i++){
            _childrens.at(i)->render();
        }
    }
}

void Component::setTexture(SDL_Texture *texture){
    if(!Error<SDL_Texture>::isNull(_texture)){
        SDL_DestroyTexture(_texture);
    }
    _texture = texture;
}

void Component::setRenderToMe(){
    if(SDL_SetRenderTarget(_renderer, _texture) != 0){
        Program::exit(EXIT_FAILURE, "Error when try to set the render target");
    }
}

void Component::appendChild(Component *child){
    _childrens.push_back(child);
}

Component::Component(Component *parent,Size size, Position position): _parent(parent),_size(size),_position(position){
    if(!Error<Component>::isNull(_parent)){
        _renderer = parent->_renderer;
        parent->appendChild(this);
    }
}

Component::~Component(){
    if(Error<SDL_Texture>::isNull(_texture)){
        Utils::cout("Destroy texture");
        SDL_DestroyTexture(_texture);
    }
   Utils::cout("Destroy component");
}