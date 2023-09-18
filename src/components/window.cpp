#include "../include/components/window.hpp"

using namespace Sdlk;

//Window Informations
std::string Window::getTitle(){
    if(!Error<SDL_Window>::isNull(_sdl_window, "Cannot get the title, because the window is null")){
        return SDL_GetWindowTitle(_sdl_window);
    }
    
    return "";
}

Position Window::getPosition(){
    int x = -1, y = -1;
    if(!Error<SDL_Window>::isNull(_sdl_window, "Cannot get the position because the window is null")){
        SDL_GetWindowPosition(_sdl_window, &x, &y);
    }
    
    return Position(x,y);
}

void Window::setTitle(std::string newTitle){
    if(!Error<SDL_Window>::isNull(_sdl_window, "Cannot set the title because the window is null")){
        SDL_SetWindowTitle(_sdl_window, newTitle.c_str());
    }
}

void Window::setPosition(Position newPosition){
    if(!Error<SDL_Window>::isNull(_sdl_window, "Cannot set the position because the window is null")){
        SDL_SetWindowPosition(_sdl_window, newPosition._x, newPosition._y);
    }
}

Window::Window( std::string title, int w, int h, Position position):Component(nullptr){
    _sdl_window = SDL_CreateWindow(
        title.c_str(),position._x ,position._y, w, h,
        SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN
    );
    
    if(Error<SDL_Window>::isNull(_sdl_window)){
        Program::exit(EXIT_FAILURE, "Cannot create window " + title);
        return;
    }

    _renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if(Error<SDL_Renderer>::isNull(_renderer)){
        Program::exit(EXIT_FAILURE, "Cannot create renderer for " + title); 
        return;
    }
    
    setColor(Rgb(255,255,255));
}

Window::~Window(){
    if(_renderer != nullptr){
        Utils::cout("Destroy render for " + getTitle());
        SDL_DestroyRenderer(_renderer);
    }
    
    if(_sdl_window != nullptr){
        Utils::cout("Destroy window " + getTitle());
        SDL_DestroyWindow(_sdl_window);
    }
}
