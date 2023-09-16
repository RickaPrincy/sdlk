#ifndef __SDLK_WINDOW_EVENT__
#define __SDLK_WINDOW_EVENT__
    #include <SDL2/SDL.h>
    #include <map>

    namespace Sdlk{
        enum WindowEventType {
            WINDOW_SHOWN,         // Window shown
            WINDOW_HIDDEN,        // Window hidden
            WINDOW_EXPOSED,       // Window exposed (partially or fully)
            WINDOW_MOVED,         // Window moved
            WINDOW_RESIZED,       // Window resized
            WINDOW_SIZE_CHANGED,  // Window size changed
            WINDOW_MINIMIZED,     // Window minimized
            WINDOW_MAXIMIZED,     // Window maximized
            WINDOW_ENTER,         // Mouse cursor entered the window
            WINDOW_LEAVE,         // Mouse cursor left the window
            WINDOW_FOCUS_LOST,    // Window lost focus
            WINDOW_CLOSE          // Window close requested
        };

        class WindowEvent{
            private:
                std::map<WindowEventType, bool> _allEvents;
            public: 
                WindowEvent();
                void updateEventState(WindowEventType event, bool newState);
                bool checkEventState(WindowEventType event);
                bool isStateTrue(WindowEventType event);
                bool isStateFalse(WindowEventType event);
        };
    }
#endif