#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
    App game("Ricka",Size(500));

    Box container(Size(500, 100));
    game._window->_box.appendChild(&container);
    game.run();
    return 0;
}
