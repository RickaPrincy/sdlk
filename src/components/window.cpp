#include "../include/components/window.hpp"

using namespace Sdlk;

//Window Informations
std::string Window::getTitle(){
    return _window == nullptr ? "" : SDL_GetWindowTitle(_window);
}

Position Window::getPosition(){
    int x = -1, y = -1;
    if(_window != nullptr){
        SDL_GetWindowPosition(_window, &x, &y);
    }
    
    return Position(x,y);
}

void Window::setTitle(std::string newTitle){
    SDL_SetWindowTitle(_window, newTitle.c_str());
}

void Window::setPosition(Position newPosition){
    SDL_SetWindowPosition(_window, newPosition._x, newPosition._y);
}

Window::Window(
    Component *parent, std::string title, int w, int h, 
    int x, int y, bool createRenderer
):Component(parent){
    _window = SDL_CreateWindow(
        title.c_str(),x ,y, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    
    if(_window == nullptr){
        Utils::cerr("Cannot create window " + title);
        exit(EXIT_FAILURE);
    }

    if(parent == nullptr){
        _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
        if(_renderer == nullptr){
            Utils::cerr("Cannot create main renderer" + title);
            exit(EXIT_FAILURE);
        }
    }
}

Window::~Window(){
    if(_window != nullptr){
        Utils::cout("Destroy window " + getTitle());
        SDL_DestroyWindow(_window);
    }
}
