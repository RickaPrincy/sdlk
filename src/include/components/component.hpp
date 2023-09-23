#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <vector>
    #include <SDL2/SDL.h>
    #include "../utils/program.hpp"
    #include "../utils/check.hpp"
    #include "../utils/utils.hpp"
    #include "../types/rgb.hpp"
    #include "../types/position.hpp"
    #include "../types/size.hpp"

    namespace Sdlk{
        class Component{
            protected:
                Size _size;
                Position _position;
                Rgb _color;
                Component *_parent = nullptr;
                std::vector<Component*> _childrens;
            public:
                SDL_Texture *_texture = nullptr;
                void setSize(Size size);
                void setColor(Rgb color);
                void setPosition(Position position);
                void setTexture(SDL_Texture *texture);
                void appendChild(Component *component);
                virtual void render(SDL_Renderer *renderer);
                Component(Size size = Size(10),Position position = Position(0));
                ~Component();
        };
    }

#endif