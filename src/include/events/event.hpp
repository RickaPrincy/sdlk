#ifndef __SDLK_EVENT__
#define __SDLK_EVENT__

    #include <SDL2/SDL.h>
    #include "../utils/utils.hpp"
    #include "../utils/program.hpp"
    #include "./mouseEvent.hpp"
    #include "./mouse.hpp"
    #include "./windowEvent.hpp"
    #include "../types/position.hpp"

    namespace Sdlk{
        class Event{
            public:
                static MouseEvent _mouseEvents;
                static WindowEvent _windowEvents;
                static void handlerAllEvents();
        };
    }
#endif