#include <sdl_kit/sdlk.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Sdlk::App myApp("R_Chess",Sdlk::Size(500));
    
    myApp.run();
    return 0;
}
