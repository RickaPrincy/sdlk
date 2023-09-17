#include <sdl_kit/sdlk.hpp>

int main(int argc, char const *argv[]){
    Sdlk::App myApp(SDL_INIT_EVERYTHING);
    Sdlk::Window mainWindow(nullptr,"Test",400,400);
    
    myApp._mainWindow = &mainWindow;

    SDL_RenderPresent(mainWindow._renderer);

    // myApp.run();
    Sdlk::Utils::wait(5000);
    return 0;
}
