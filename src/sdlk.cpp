#include "./include/sdlk.hpp"

using namespace Sdlk;

void App::initSdl(Uint32 flags){
    _flags.insert(flags);
    if (SDL_WasInit(flags) != 0 && SDL_InitSubSystem(flags) != 0){
        Utils::cerr("Error when try to initialise SDL");
        exit(EXIT_FAILURE);
    }
    Utils::cout("SDL init");
}

void App::run(){
    if(_mainWindow != NULL){
        while(true){
            _event.handlerAllEvents();
        }
    }

    Utils::cerr("Main window cannot be NULL");
}

App::App(Uint32 flags){
    initSdl(flags);
}

App::App(Uint32 flags, Window *mainWindow): _mainWindow(mainWindow){
    initSdl(flags);
}

App::~App(){
    Utils::cout("SDL Quit");
    SDL_Quit();
}