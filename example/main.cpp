#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
    App game("Ricka",Size(500));

    Box container(Size(500, 100));
    container.setColor(Rgb(255,255,1));

    Box cool(Size(20, 20), Position(100,0));
    cool.setColor(Rgb(155,15,1));
    
    container.appendChild(&cool);
    game.appendChild(&container);
    game.run();
    return 0;
}
