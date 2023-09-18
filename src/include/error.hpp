#ifndef __SDLK_ERROR__
#define __SDLK_ERROR__
    #include <iostream> 
    #include <string>
    #include "./utils.hpp"

    namespace Sdlk{
        template<typename T>
        class Error{
            public:
                static bool isNull(T *ptr, std::string message = ""){
                    if(ptr == nullptr || ptr == NULL){
                        if(message != ""){
                            Utils::cerr(message);
                        }

                        return true;
                    }
                    return false;
                }
        };
    }
#endif