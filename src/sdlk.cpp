#include "./include/sdlk.hpp"

using namespace Sdlk;

void App::initSdl(Uint32 flags){
    if (SDL_WasInit(flags) != 0 && SDL_InitSubSystem(flags) != 0){
        Program::exit(EXIT_FAILURE,"Error when try to initialise SDL");
    }
    Utils::cout("SDL init");
}

void App::run(){
    Program::start();
    Program::setShouldRenderer(true);

    while(Program::getStatus()){
        if(!Error<SDL_Window>::isNull(_window->_sdl_window, "Window cannot be null")){
            _event.handlerAllEvents();

            if(Program::getShouldRenderer()){
                _window->render();
                Program::setShouldRenderer(false);

                Utils::cout("render");
            }

            Utils::wait(1);
        }
    }
}


App::App( std::string name, int w, int h,  Position position, Uint32 flags){
    initSdl(flags);
    _window = new Window(name, w, h,position);
}

App::~App(){
    delete _window;
    Utils::cout("SDL Quit");
    SDL_Quit();
}