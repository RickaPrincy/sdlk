#include "./include/sdlk.hpp"

using namespace Sdlk;

SDL::SDL(Uint32 flags) : _flags(flags){
    if (SDL_WasInit(flags) != 0 && SDL_InitSubSystem(flags) != 0){
        Utils::cerr("Error when try to initialise SDL");
        exit(EXIT_FAILURE);
    }
    Utils::cout("SDL init");
}

SDL::~SDL(){
    if (SDL_WasInit(_flags) == 0){
        SDL_QuitSubSystem(_flags);
        Utils::cout("SDL Quit");
    }
}