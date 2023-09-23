#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
    App myApp("est",Size(500));

    Component first(Size(100),Position(55));
    first.setColor(Rgb(255,0,0));
    
    Component second(Size(50));
    second.setColor(Rgb(0,255,0));

    first.appendChild(&second);
    myApp._window->_component.appendChild(&first);

    myApp.run();
    return 0;
}
