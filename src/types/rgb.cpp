#include "../include/utils/utils.hpp"
#include "../include/types/rgb.hpp"
#include "../include/types/position.hpp"
#include "../include/types/size.hpp"

using namespace Sdlk;

const std::regex Rgb::_format("r:(\\d+),g:(\\d+),b:(\\d+)");

//----------------------------------------------------------------
Rgb::Rgb(){}

Rgb::Rgb(int r, int g, int b){
    if(r > 255 || r < 0 || g > 255 || g < 0 || b > 255 || b < 0){
        std::cerr << "Rgb value not valid (min : 0, max : 255)" << std::endl;
        return;
    }
    _r = r;
    _g = g;
    _b = b;
}

Rgb::Rgb(std::string input){
    *this = input;
}

//----------------------------------------------------------------
Rgb& Rgb::operator=(const std::string& other) {
    *this = fromString(other);
    return *this;
}

Rgb& Rgb::operator=(const Rgb& other) {
    if (this != &other) {
        _r = other._r;
        _g = other._g;
        _b = other._b;
    }
    return *this;
}

Rgb& Rgb::operator=(const std::variant<Rgb,Size,Position,std::string> &other){
    if(std::holds_alternative<std::string>(other)){
        *this = std::get<std::string>(other);
    }
    else if(std::holds_alternative<Rgb>(other)){
        *this = std::get<Rgb>(other);
    }
    return *this;
}

//----------------------------------------------------------------
Rgb Rgb::fromString(std::string input){
    std::smatch match;
    std::string removedSpace = Utils::removeSpace(input);
    int _r = 255, _g = 255 , _b = 255;

    if(std::regex_match(removedSpace, match, _format)){
        _r = std::stoi(match.str(1));
        _g = std::stoi(match.str(2)); 
        _b = std::stoi(match.str(3)); 
    }
    
    return Rgb(_r,_g,_b);
}