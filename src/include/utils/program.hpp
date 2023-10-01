#ifndef __SDLK_PROGRAM__
#define __SDLK_PROGRAM__

    #include <iostream>
    #include <string>
    #include "./utils.hpp"
    #define EXIT_STATUS short
    
    namespace Sdlk{

        enum ExitStatus{
            FAILURE,
            SUCCESS
        };

        class Program{
            private: 
                static bool programLaunched;
            public:
                static bool getStatus();
                static void start();
                static void exit(ExitStatus status = ExitStatus::SUCCESS, std::string message = "");
        };
    } 
#endif