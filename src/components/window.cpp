#include "../include/components/window.hpp"

using namespace Sdlk;

void Window::render(){
    _component.render(_renderer);
    SDL_RenderPresent(_renderer);
}

Window::Window(std::string title, Size size, Position position, Uint32 flags){
    _sdl_window = SDL_CreateWindow(
        title.c_str(),
        position._x, 
        position._y,
        size._w,
        size._h,
        flags
    );

    if(Check::isNull(_sdl_window)){
        Program::exit(ExitStatus::FAILURE, "Cannot create a window for " + title);
        return;
    }

    _renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED);
    if(Check::isNull(_renderer)){
        Program::exit(ExitStatus::FAILURE, "Cannot create a renderer for " + title);
        return;
    }

    _component.setSize(size);
    _component.setTexture(nullptr);
    _component.setColor(Rgb(255,255,255));
}

Window::~Window(){
    _component.~Component();
    if(!Check::isNull(_renderer)){
        Utils::clog("Destroy renderer");
        SDL_DestroyRenderer(_renderer);
    }

    if(!Check::isNull(_sdl_window)){
        Utils::clog("Destroy window");
        SDL_DestroyWindow(_sdl_window);
    }
}

