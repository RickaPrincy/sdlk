#ifndef __SDLK__
#define __SDLK__
    #include <iostream>
    #include <set>
    #include <SDL2/SDL.h>

    #include "./utils.hpp"
    #include "./events/event.hpp"
    #include "./types/position.hpp"
    #include "./components/window.hpp"

    namespace Sdlk{
        class App{
            private: 
                std::set<Uint32> _flags;
            public:
                Event _event;
                Window *_mainWindow;

                void initSdl(Uint32 flags);
                void run();

                App(Uint32 flags);
                App(Uint32 flags, Window *mainWindow);
                ~App();
        };
    }

#endif