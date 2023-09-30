#ifndef __SDLK_UTILS__
#define __SDLK_UTILS__
    #include <iostream>
    #include <string>
    #include <SDL2/SDL.h>
    #include "../types/rgb.hpp"

    namespace Sdlk{
        class Utils{
            public:
                static void clog(std::string message);
                static void cerr(std::string message);
                static void wait(Uint32 delay);
                static bool setRenderTarget(SDL_Renderer *renderer, SDL_Texture *texture);
                static bool setRenderColor(SDL_Renderer *renderer, Rgb color);
                static bool renderCopy(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *rect_src, SDL_Rect *rect_dst);
                static bool clearRenderer(SDL_Renderer *renderer);
                static std::string removeSpace(std::string input);
        };
    }
#endif