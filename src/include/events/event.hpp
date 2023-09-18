#ifndef __SDLK_EVENT__
#define __SDLK_EVENT__

    #include <SDL2/SDL.h>
    #include "../utils.hpp"
    #include "../program.hpp"
    #include "./mouseEvent.hpp"

    namespace Sdlk{
        class Event{
            public:
                MouseEvent _mouseEvents;
                void handlerAllEvents();
        };
    }
#endif