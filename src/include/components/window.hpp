#ifndef __SDLK_WINDOW__
#define __SDLK_WINDOW__

    #include <iostream>
    #include <SDL2/SDL.h>

    #include "../utils.hpp"
    #include "../types/position.hpp"

    namespace Sdlk{
        class Window{
            public:
                //Maybe utils for user
                SDL_Window *_window = NULL;

                //Window informations 
                std::string getTitle();
                Position getPosition();
                
                void setTitle(std::string newTitle);
                void setPosition(Position newPosition);
                
                //Constructor && Deconstructor
                Window(std::string title, int w, int h);
                Window(std::string title, int w, int h, int x, int y);
                ~Window();
        };
    }
#endif