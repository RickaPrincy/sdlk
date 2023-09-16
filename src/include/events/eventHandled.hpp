#ifndef __SDLK_EVENT_HANDLER__
#define __SDLK_EVENT_HANDLER__
    #include <iostream> 
    #include <map>

    namespace Sdlk{

        template <typename T>
        class EventHandled{
            protected:
                std::map<T, bool> _allEvents;
            public: 
                void updateState(T event, bool newState);
                bool checkState(T event);
                bool hasOccured(T event);
                bool hasNotOccured(T event);
        };
    }
#endif