# sdlk is SDL2 wrapper

```cpp
#include <sdl_kit/app.hpp>
#include <iostream>

using namespace Sdlk;
int main(int argc, char const *argv[]){
  Box leftBox({
    { Attribute::COLOR, "r: 255, g: 0, b: 0" },
    { Attribute::SIZE, "w: 50, h: 50"}
  });

  Box centerBox({
    { Attribute::COLOR, "r: 0, g: 0, b: 255" },
    { Attribute::SIZE, "w: 50, h: 50"},
    { Attribute::POSITION, "x: 250, y: 50"}
  });

  Box rightBox({
    { Attribute::SIZE, leftBox.getOneStyle<Size>(Attribute::SIZE)},
    { Attribute::POSITION, "x: 450, y: 0"}
  });

  Box navbar({
    {Attribute::SIZE, Size(500, 100)},
    {Attribute::COLOR, Rgb(0,255,0)}
  });

  leftBox.onClick([&](){
    navbar.updateStyle({
      { Attribute::COLOR, leftBox.getOneStyle<Rgb>(Attribute::COLOR) },
    });
    Utils::clog("Hello");
  });

  rightBox.onClick([&](){
    navbar.updateStyle({
      { Attribute::COLOR, rightBox.getOneStyle<Rgb>(Attribute::COLOR) },
    });
  });

  centerBox.onHover([&](){
    navbar.updateStyle({
      { Attribute::COLOR, centerBox.getOneStyle<Rgb>(Attribute::COLOR) },
    });
  });

  navbar.onRender([](){
    Utils::clog("Render navbar");
  });

  App app("R_Chess", Size(500));
  std::vector<Component*> childs = { &leftBox, &rightBox, &centerBox };

  navbar.appendChilds(childs);

  app.appendChild(&navbar);
  app.run();
  
  return 0;
}
```
