#include <sdl_kit/sdlk.hpp>

int main(int argc, char const *argv[]){
    Sdlk::App myApp(SDL_INIT_EVERYTHING);
    Sdlk::Window myFrstWindow("Test",400,400);
    myApp._mainWindow = &myFrstWindow;

    // myApp.run();

    Sdlk::Utils::wait(5000);
    return 0;
}
