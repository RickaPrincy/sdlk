#include "../include/components/window.hpp"
#include "../include/events/event.hpp"

using namespace Sdlk;

Size Window::getSize(){
    int x = 1, y = 1;
    
    if(!Check::isNull(_sdl_window)){
        SDL_GetWindowSize(_sdl_window, &x, &y);
    }
    return Size(x,y);
}

void Window::render(){
    if(Event::_windowEvents.hasOccured(WindowEventType::WINDOW_RESIZED)){
        _box.updateStyle({
            { Attribute::SIZE, getSize() }
        });
    }
    _box.handlerEvent();
    _box.render(_renderer);
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

    _box.updateStyle({
        { Attribute::SIZE, size },
        { Attribute::COLOR, "r: 255, g: 255, b: 255"}
    });
}

Window::~Window(){
    if(!Check::isNull(_renderer)){
        Utils::clog("Destroy renderer");
        SDL_DestroyRenderer(_renderer);
    }

    if(!Check::isNull(_sdl_window)){
        Utils::clog("Destroy window");
        SDL_DestroyWindow(_sdl_window);
    }
}

