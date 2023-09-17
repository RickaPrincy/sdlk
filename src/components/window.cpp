#include "../include/components/window.hpp"

using namespace Sdlk;

//Window Informations
std::string Window::getTitle(){
    return _window == NULL ? "" : SDL_GetWindowTitle(_window);
}

Position Window::getPosition(){
    int x = -1, y = -1;
    if(_window != NULL){
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

//Constructor && Deconstructor
Window::Window(std::string title, int w, int h){
    _window = SDL_CreateWindow(
        title.c_str(), 
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED,
        w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );

    if(_window == NULL){
        Utils::cerr("Cannot create window " + title);
        exit(EXIT_FAILURE);
    }
}

Window::Window(std::string title, int w, int h, int x, int y){
    _window = SDL_CreateWindow(
        title.c_str(),x ,y, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    
    if(_window == NULL){
        Utils::cerr("Cannot create window " + title);
        exit(EXIT_FAILURE);
    }
}

Window::~Window(){
    if(_window != NULL){
        Utils::cout("Destroy window " + getTitle());
        SDL_DestroyWindow(_window);
    }
}
