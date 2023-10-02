#ifndef __SDLK_COMPONENT_EVENT__
#define __SDLK_COMPONENT_EVENT__

    #include "./eventHandled.hpp"

    namespace Sdlk{
        enum ComponentEventType{
            CLICK,
            HOVER,
            RENDER
        };

        class ComponentEvent : public EventHandled<ComponentEventType>{
            public:
                ComponentEvent();
        };
    }
#endif