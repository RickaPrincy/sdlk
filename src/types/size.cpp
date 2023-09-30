#include "../include/utils/utils.hpp"
#include "../include/types/rgb.hpp"
#include "../include/types/position.hpp"
#include "../include/types/size.hpp"

using namespace Sdlk;

const std::regex Size::_format("w:(\\d+),h:(\\d+)");

Size Size::fromString(std::string input){
    std::smatch match;
    std::string removedSpace = Utils::removeSpace(input);
    int _w = 10, _h = 10;

    if(std::regex_match(removedSpace, match, _format)){
        _w = std::stoi(match.str(1));
        _h = std::stoi(match.str(2)); 
    }
    
    return Size(_w,_h);
}

Size::Size(int w, int h){
    if(w < 10 || h < 10 ){
        std::cerr << "Size value not valid (min : 10)" << std::endl;
        return;
    }
    _w = w;
    _h = h;
}

Size::Size(int wh){
    *this = Size(wh, wh);
}

Size::Size(std::string input){
    *this = input;
}

Size& Size::operator=(const std::string& other) {
    *this = fromString(other);
    return *this;
}

Size& Size::operator=(const Size& other) {
    if (this != &other) {
        _w = other._w;
        _h = other._h;
    }
    return *this;
}

Size& Size::operator=(const std::variant<Rgb,Size,Position,std::string> &other){
    if(std::holds_alternative<std::string>(other)){
        *this = std::get<std::string>(other);
    }
    else if(std::holds_alternative<Size>(other)){
        *this = std::get<Size>(other);
    }

    return *this;
}