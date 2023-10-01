#include "../include/types/style.hpp"

using namespace Sdlk;

//----------------------------------------------------------------
Style::Style(){}
Style::Style(StyleArg style){ updateStyle(style); }

//----------------------------------------------------------------
Style& Style::operator=(const Style &other){
    updateStyle(other);
    return *this;
}

Style& Style::operator=(const StyleArg &other){
    updateStyle(other);
    return *this;
}

//----------------------------------------------------------------
void Style::updateStyle(Attribute key, StyleVariant value){
    switch(key){
        case Attribute::COLOR:
            _color = value;
            _style.at(key) = _color;
            break;
        case Attribute::SIZE:
            _size = value;
            _style.at(key) = _size;
            break;
        case Attribute::POSITION:
            _position = value;
            _style.at(key) = _position;
            break;
        default:
            break;
    }
}

void Style::updateStyle(StyleArg style){
    for(const auto pair : style){
        updateStyle(pair.first, pair.second);
    }
}

void Style::updateStyle(Style style){  updateStyle(style.getAllStyles()); }