#include "../include/utils/program.hpp"

using namespace Sdlk;

bool Program::getStatus(){
    return programLaunched;
}

void Program::start(){
    programLaunched = true;
}

void Program::exit(ExitStatus status, std::string message){
    if(message != ""){
        if(status == ExitStatus::FAILURE){
            Utils::cerr(message);
        }else{
            Utils::clog(message);
        }
    }
    programLaunched = false; 
}