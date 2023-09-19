#ifndef __SDLK_EXIT__
#define __SDLK_EXIT__
    #define EXIT_STATUS int
    
    #include <string> 
    #include "./utils.hpp"

    namespace Sdlk{
        static bool programLaunched = false;
        class Program{
            public:
                static void start();
                static bool getStatus();
                static void exit(EXIT_STATUS status,std::string message = "");
        };
    }
#endif