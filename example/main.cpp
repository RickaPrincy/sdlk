#include <sdl_kit/sdlk.hpp>
#include <iostream>

int main(int argc, char const *argv[]){
    Sdlk::App myApp("LOL",Sdlk::Size(500));

    Sdlk::Component test(myApp._window,Sdlk::Size(200), Sdlk::Position(0));
    test.setColor(Sdlk::Rgb(255,0,0));

    myApp.run();
    return 0;
}
