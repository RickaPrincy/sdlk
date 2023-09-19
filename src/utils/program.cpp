#include "../include/program.hpp"

using namespace Sdlk;

bool Program::getStatus(){
    return programLaunched;
}

void Program::start(){
    programLaunched = true;
}

void Program::exit(EXIT_STATUS status, std::string message){
    if(message != ""){
        if(status == EXIT_FAILURE){
            Utils::cerr(message);
        }else{
            Utils::cout(message);
        }
    }
   programLaunched = false; 
}