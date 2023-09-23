#ifndef __SDLK_CHECK__
#define __SDLK_CHECK__

    namespace Sdlk{
        class Check{
            public:
                template <typename T>
                static bool isNull(T *ptr){
                    return ptr == NULL || ptr == nullptr;
                }
        };
    }
#endif