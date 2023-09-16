#include <sdl_kit/sdlk.hpp>

int main(int argc, char const *argv[]){
    Sdlk::SDL App(SDL_INIT_EVERYTHING);
    Sdlk::Window firstWindow("My favourite game", 400, 400);

    std::cout << firstWindow.getTitle() << std::endl;

    Sdlk::Positions test = firstWindow.getPositions();
    std::cout << firstWindow.getPositions()._x << std::endl;
    std::cout << firstWindow.getPositions()._y << std::endl;
    
    return 0;
}
