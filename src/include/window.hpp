#ifndef __SDLK_WINDOW__
#define __SDLK_WINDOW__

    #include <iostream>
    #include <SDL2/SDL.h>

    #include "./utils.hpp"
    #include "./types.hpp"

    namespace Sdlk{
        class Window{
            private: 
                std::string _title;
                SDL_Window *_window = NULL;
            public:
                std::string getTitle();
                void setTitle(std::string newTitle);
                Positions getPositions();
                Window(std::string title, int w, int h);
                Window(std::string title, int w, int h, int x, int y);
                ~Window();
        };
    }
#endif