#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <SDL2/SDL.h>
    #include <vector>
    #include "../types/visibility.hpp"
    #include "../utils.hpp"
    #include "../error.hpp"
    #include "../types/rgb.hpp"
    #include "../types/position.hpp"
    #include "../types/size.hpp"
    #include "../program.hpp"
    
    namespace Sdlk{
        class Component{
            protected:
                SDL_Renderer *_renderer = nullptr;
                SDL_Texture *_texture = nullptr;
                Rgb _color;
                Position _position;
                Size _size;
                Component *_parent = nullptr;
                std::vector<Component*> _childrens;
            public:
                void setColor(Rgb color);
                void render();
                void setRenderToMe();
                void appendChild(Component *child);
                void setTexture(SDL_Texture *texture);
                static void releaseRenderer(SDL_Renderer *renderer);
                static void clearRenderer(SDL_Renderer *renderer);
                Component(Component *parent, Size size, Position position);
                ~Component();
        };
    }
#endif