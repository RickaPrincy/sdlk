#include "../include/utils.hpp"

using namespace Sdlk;

void Utils::cout(std::string message){
    std::cout << "[ LOG ]: " << message << std::endl;
}

void Utils::cerr(std::string error){
    std::cerr << "[ ERR ]: " << error << std::endl;
}

void Utils::wait(Uint32 ms){
    SDL_Delay(ms);
}