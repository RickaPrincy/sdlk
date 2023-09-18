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

        template <typename T>
        void EventHandled<T>::updateState(T event, bool newState){
            _allEvents[event] = newState;
        }

        template <typename T>
        bool EventHandled<T>::checkState(T event){
            return _allEvents[event];
        }

        template <typename T>
        bool EventHandled<T>::hasOccured(T event){
            return checkState(event);
        }

        template <typename T>
        bool EventHandled<T>::hasNotOccured(T event){
            return !checkState(event);
        }
    }
#endif