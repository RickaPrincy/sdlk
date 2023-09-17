#include "../include/events/event.hpp"

using namespace Sdlk;

void Event::handlerAllEvents(){
    SDL_Event event;
    
    while(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                exit(EXIT_SUCCESS);
                break;
            case SDL_WINDOWEVENT:
                break;
            case SDL_KEYDOWN:
                break;
            case SDL_KEYUP:
                break;
            case SDL_MOUSEMOTION:
                break;
            case SDL_MOUSEBUTTONDOWN:
                break;
            case SDL_MOUSEWHEEL:
                break;
            default: 
                Sdlk::Utils::cout("Event not handled yet");
                break;
        }
    }
}