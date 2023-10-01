#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
  App app("MyGame", Size(500));

  Box container({
    { Attribute::COLOR, "r: 255, g: 0, b: 200" },
    { Attribute::SIZE, "w: 100, h: 100"},
    { Attribute::POSITION, "x: 5, y : 9"}
  });

  app._window->_box.onClick([](){
    Utils::clog("Cliked");
    Utils::clog("Yeah");
  });

  app.appendChild(&container);
  app.run();
  return 0;
}