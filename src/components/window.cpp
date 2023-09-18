#include "../include/components/window.hpp"

using namespace Sdlk;

//Window Informations
std::string Window::getTitle(){
    return _sdl_window == nullptr ? "" : SDL_GetWindowTitle(_sdl_window);
}

Position Window::getPosition(){
    int x = -1, y = -1;
    if(_sdl_window != nullptr){
        SDL_GetWindowPosition(_sdl_window, &x, &y);
    }
    
    return Position(x,y);
}

void Window::setTitle(std::string newTitle){
    SDL_SetWindowTitle(_sdl_window, newTitle.c_str());
}

void Window::setPosition(Position newPosition){
    SDL_SetWindowPosition(_sdl_window, newPosition._x, newPosition._y);
}

Window::Window(
    Component *parent, std::string title, 
    int w, int h, Position position
):Component(parent){
    _sdl_window = SDL_CreateWindow(
        title.c_str(),position._x ,position._y, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    
    if(_sdl_window == nullptr){
        Program::exit(EXIT_FAILURE, "Cannot create window " + title);
        return;
    }

    if(_parent == nullptr || _parent == NULL){
        _renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED);
        if(_renderer == nullptr){
            Program::exit(EXIT_FAILURE, "Cannot create renderer for " + title); 
        }
    }
}

Window::~Window(){
    if(_parent == nullptr && _renderer != nullptr){
        Utils::cout("Destroy render for " + getTitle());
        SDL_DestroyRenderer(_renderer);
    }
    
    if(_sdl_window != nullptr){
        Utils::cout("Destroy window " + getTitle());
        SDL_DestroyWindow(_sdl_window);
    }
}
