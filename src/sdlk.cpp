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

    if(_window != nullptr){
        while(Program::getStatus()){
            _event.handlerAllEvents();
            _window->render();
            Utils::wait(1);
        }
    }else{
        Utils::cerr("Main window cannot be null");
    }
}


App::App( std::string name, int w, int h,  Position position, Uint32 flags){
    initSdl(flags);
    _window = new Window(nullptr,name, w, h,position);
}

App::~App(){
    delete _window;
    Utils::cout("SDL Quit");
    SDL_Quit();
}