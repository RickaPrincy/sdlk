#include "../include/types/position.hpp"
#include "../include/types/size.hpp"
#include "../include/types/rgb.hpp"
#include "../include/utils/utils.hpp"

using namespace Sdlk;
const std::regex Position::_format("x:(\\d+),y:(\\d+)");

//----------------------------------------------------------------
Position::Position():_x(0),_y(0){};
Position::Position(int x ,int y):_x(x),_y(y){};
Position::Position(int xy):_x(xy),_y(xy){};
Position::Position(std::string input){ *this = input; }

//----------------------------------------------------------------
Position& Position::operator=(const Position& other) {
    if (this != &other) {
        _x = other._x;
        _y = other._y;
    }
    return *this;
}

Position& Position::operator=(const std::string& other) {
    *this = fromString(other);
    return *this;
}

Position& Position::operator=(const std::variant<Rgb,Size,Position,std::string> &other){
    if(std::holds_alternative<std::string>(other)){
        *this = std::get<std::string>(other);
    }
    else if(std::holds_alternative<Position>(other)){
        *this = std::get<Position>(other);
    }

    return *this;
}

//----------------------------------------------------------------
Position Position::fromString(std::string input){
    std::smatch match;
    std::string removedSpace = Utils::removeSpace(input);
    int _x = 0, _y = 0 ;

    if(std::regex_match(removedSpace, match, _format)){
        _x = std::stoi(match.str(1));
        _y = std::stoi(match.str(2)); 
    }
    
    return Position(_x,_y);
}