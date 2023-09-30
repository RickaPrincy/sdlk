#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
  App app("Ricka", Size(500));

  Box container({
    { Attribute::COLOR, "r:255,g: 0, b: 0" }
  });

  app.appendChild(&container);
  app.run();
  return 0;
}
