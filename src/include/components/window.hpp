#ifndef __SDLK_WINDOW__
#define __SDLK_WINDOW__

    #include <iostream>
    #include <SDL2/SDL.h>

    #include "../utils.hpp"
    #include "../types/position.hpp"
    #include "../components/component.hpp"

    namespace Sdlk{
        class Window: public Component{
            public:
                //Maybe utils for user
                SDL_Window *_window = nullptr;

                //Window informations 
                std::string getTitle();
                Position getPosition();
                
                void setTitle(std::string newTitle);
                void setPosition(Position newPosition);
                
                //Constructor && Deconstructor
                Window(
                    Component *parent,std::string title, int w, int h, 
                    int x = 0, int y = 0, bool createRenderer = false 
                );
                ~Window();
        };
    }
#endif