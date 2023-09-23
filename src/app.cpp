#include "./include/app.hpp"

using namespace Sdlk;

void App::run(){
    Program::start();
    if(!Check::isNull(_window)){
        while(Program::getStatus()){
            _event.handlerAllEvents();
            _window->render();
        }
    }
}

void App::appendChild(Component *child){
    _window->_box.appendChild(child);
}

void App::initSdl(Uint32 flags){
    if(SDL_WasInit(flags) != 0 && SDL_InitSubSystem(flags) != 0){
        Program::exit(ExitStatus::FAILURE, "Cannot init sdl");
    }
}

void App::quitSdl(Uint32 flags){
    SDL_QuitSubSystem(flags);
}

App::App(std::string title, Size size, Position position, Uint32 flags){
    if(SDL_Init(flags) != 0){
        Program::exit(ExitStatus::FAILURE, "Cannot init sdl");
        return;
    }
    _window = new Window(title,size, position);
}

App::~App(){
    delete _window;
}
