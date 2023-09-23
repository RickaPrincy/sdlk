#include "../include/utils/utils.hpp"

using namespace Sdlk;

void Utils::clog(std::string message){
    std::cout << "[ LOG ]: " << message << std::endl;
}

void Utils::cerr(std::string error){
    std::cerr << "[ ERR ]: " << error << " + SDL_Error: " << SDL_GetError() << std::endl;
}

void Utils::wait(Uint32 delay){
    SDL_Delay(delay);
}

bool Utils::setRenderTarget(SDL_Renderer *renderer, SDL_Texture *texture){
    if(SDL_SetRenderTarget(renderer,texture) != 0){
        Utils::cerr("Cannot set the target of renderer");
        return false;
    }
    return true;
}


bool Utils::setRenderColor(SDL_Renderer *renderer, Rgb color){
    if(SDL_SetRenderDrawColor(renderer,color._r,color._g,color._b, 255) != 0){
        Utils::cerr("Cannot set the color of renderer");
        return false;
    }
    return true;
}

bool Utils::renderCopy(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect_src, SDL_Rect *rect_dst){
    if(SDL_RenderCopy(renderer,texture,rect_src,rect_dst) != 0){
        Utils::cerr("Cannot copy the texture");
        return false;
    }
    return true;
}

bool Utils::clearRenderer(SDL_Renderer *renderer){
    if(SDL_RenderClear(renderer) != 0){
        Utils::cerr("Cannot clear renderer");
        return false;
    }
    return true;
}