#ifndef __SDLK_MOUSE_EVENT__
#define __SDLK_MOUSE_EVENT__

    #include <map>
    #include "./eventHandled.hpp" 

    namespace Sdlk{
        enum MouseEventType {
            MOUSE_NO_EVENT,        // No mouse event occurred
            MOUSE_BUTTON_DOWN,     // Mouse button was pressed
            MOUSE_BUTTON_UP,       // Mouse button was released
            MOUSE_SINGLE_CLICK,    // Mouse button was clicked once
            MOUSE_DOUBLE_CLICK,    // Mouse button was double-clicked
            MOUSE_MANY_CLICKS,     // Multiple clicks occurred
            MOUSE_MOVE_UP,         // Mouse moved upwards
            MOUSE_MOVE_DOWN,       // Mouse moved downwards
            MOUSE_MOVE_LEFT,       // Mouse moved to the left
            MOUSE_MOVE_RIGHT,      // Mouse moved to the right
            MOUSE_DRAG_START,      // Mouse drag operation started
            MOUSE_DRAG_END,        // Mouse drag operation ended
            MOUSE_SCROLL_UP,       // Mouse scroll wheel moved up
            MOUSE_SCROLL_DOWN      // Mouse scroll wheel moved down
        };

        class MouseEvent : EventHandled<MouseEventType>{
            public: 
                MouseEvent();
        };
    }

#endif