#include "../include/types/style.hpp"

using namespace Sdlk;

StyleVariant Style::getStyle(Attribute key){
    return _style.at(key);
}

void Style::updateStyle(StyleArg style){
    for(const auto attribute: style){
        if(_style.find(attribute.first) != _style.end()){
            _style.at(attribute.first) = attribute.second; 
        }
    }
}

void Style::updateStyle(Style style){
    updateStyle(style._style);
}

Style::Style(StyleArg style){
    updateStyle(style);
}

Style& Style::operator=(const Style &other){
    updateStyle(other);
    return *this;
}

Style& Style::operator=(const StyleArg &other){
    updateStyle(other);
    return *this;
}