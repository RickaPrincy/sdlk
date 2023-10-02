#include "./include/app.hpp"

using namespace Sdlk;

void App::run(){
    Program::start();
    if(!Check::isNull(_window)){
        while(Program::getStatus()){
            Event::handlerAllEvents();

            _window->render();

            Event::_mouseEvents.resetAll();
            Event::_windowEvents.resetAll();

            limitFps(SDL_GetTicks());
        }
    }
}

void App::appendChilds(std::vector<Component*> childs){
    _window->_box.appendChilds(childs);
}

void App::appendChild(Component *child){
    _window->_box.appendChild(child);
}

void App::limitFps(unsigned int limit){
    unsigned int ticks = SDL_GetTicks();

    if(limit < ticks)
        return; 
    else if(limit > ticks + _fps_limit)
        SDL_Delay(_fps_limit);
    else 
        SDL_Delay(limit - ticks);
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
    SDL_Quit();
}
