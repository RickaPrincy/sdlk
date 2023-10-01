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
  
  Box otherBox({
    { Attribute::SIZE, Size(100)},
    { Attribute::POSITION, "x: 150, y : 150"}
  });

  Rgb test(255,1,1);

  app.appendChild(&container);
  app.appendChild(&otherBox);
  app.run();
  return 0;
}