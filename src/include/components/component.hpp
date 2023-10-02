#ifndef __SDLK_COMPONENT__
#define __SDLK_COMPONENT__

    #include <vector>
    #include <functional>
    #include <map>
    #include <SDL2/SDL.h>
    #include "../utils/program.hpp"
    #include "../utils/check.hpp"
    #include "../utils/utils.hpp"
    #include "../types/style.hpp" 
    #include "../events/event.hpp" 
    #include "../events/mouse.hpp" 
    #include "../events/componentEvent.hpp" 

    namespace Sdlk{
        class Component{
            protected:
                Style _style;
                Component *_parent = nullptr;
                Position _realPosition;
                std::vector<Component*> _childrens;
                std::map<ComponentEventType,std::function<void()>> _actions;
                void handlerClick();
                void handlerHover();
                void executeEventActions();
                void shouldExecuteEvent(ComponentEventType event);
            public:
                ComponentEvent _events;                
                SDL_Texture *_texture = nullptr;
                bool _shouldRenderer = true;

                Component();
                Component(Style style);
                Component(StyleArg style);
                ~Component();

                void makeRenderer();
                void updateStyle(StyleArg style);
                void updateStyle(Style style);
                void setTexture(SDL_Texture *texture);
                void appendChild(Component *component);
                void appendChilds(std::vector<Component*> childs);
                void calcRealPosition();
                Position getRealPosition();

                void onClick(const std::function<void()> &onClickFunction);
                void onHover(const std::function<void()> &onClickFunction);
                void onRender(const std::function<void()> &onRenderFuction);
                void handlerAllEvent();
                void resetAllEvent();

                virtual void render(SDL_Renderer *renderer);

                template <typename T>
                T getOneStyle(Attribute key) { return _style.getOneStyle<T>(key); }
        };
    }

#endif