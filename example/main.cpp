#include <sdl_kit/sdlk.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Sdlk::App myApp("R_Chess",500,500);
    
    myApp.run();
    return 0;
}
