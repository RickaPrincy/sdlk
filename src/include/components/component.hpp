#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <vector>
    #include <functional>
    #include <SDL2/SDL.h>
    #include "../utils/program.hpp"
    #include "../utils/check.hpp"
    #include "../utils/utils.hpp"
    #include "../types/style.hpp" 
    #include "../events/event.hpp" 
    #include "../events/mouse.hpp" 
    namespace Sdlk{
        class Component{
            protected:
                Style _style;
                Component *_parent = nullptr;
                std::vector<Component*> _childrens;
                std::function<void()> _onClickFunction;
                Position _realPosition;
            public:
                SDL_Texture *_texture = nullptr;

                Component();
                Component(Style style);
                Component(StyleArg style);
                ~Component();

                void updateStyle(StyleArg style);
                void updateStyle(Style style);
                void setTexture(SDL_Texture *texture);
                void appendChild(Component *component);
                void calcRealPosition();
                Position getRealPosition();

                void onClick(const std::function<void()> &onClickFunction);
                void handlerEvent();

                virtual void render(SDL_Renderer *renderer);

                template <typename T>
                T getOneStyle(Attribute key) { return _style.getOneStyle<T>(key); }
        };
    }

#endif