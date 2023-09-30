#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <vector>
    #include <SDL2/SDL.h>
    #include "../utils/program.hpp"
    #include "../utils/check.hpp"
    #include "../utils/utils.hpp"
    #include "../types/style.hpp" 

    namespace Sdlk{
        class Component{
            protected:
                Style _style;
                Component *_parent = nullptr;
                std::vector<Component*> _childrens;
            public:
                SDL_Texture *_texture = nullptr;
                
                StyleVariant getStyle(Attribute key);
                void updateStyle(StyleArg style);
                void setTexture(SDL_Texture *texture);
                void appendChild(Component *component);
                virtual void render(SDL_Renderer *renderer);

                Component(){};
                Component(Style style):_style(style){}
                Component(StyleArg style);
                ~Component();
        };
    }

#endif