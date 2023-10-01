#include "../include/events/event.hpp"

using namespace Sdlk;

WindowEvent Event::_windowEvents;
MouseEvent Event::_mouseEvents;

void Event::handlerAllEvents(){
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                Program::exit(ExitStatus::SUCCESS);
                break;
            case SDL_WINDOWEVENT:
                _windowEvents.handlerWindowEvent(&event);
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEMOTION:
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEWHEEL:
            case SDL_MOUSEBUTTONDOWN:
                _mouseEvents.handlerMouseEvent(&event);
                break;
            default: 
                Sdlk::Utils::clog("Event not handled yet");
                break;
        }
    }
}