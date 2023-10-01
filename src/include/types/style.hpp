#ifndef __SDLK_ATTRIBUTES__
#define __SDLK_ATTRIBUTES__

    #include "./attribute.lib.hpp"
    #include "./attribute.hpp"
    #include "./rgb.hpp"
    #include "./size.hpp"
    #include "./position.hpp"

    namespace Sdlk{
        using StyleVariant = std::variant<Rgb,Size,Position,std::string>;
        using StyleArg = std::map<Attribute, StyleVariant>;
        
        class Style{
            private:
                Rgb _color;
                Size _size;
                Position _position;
                StyleArg _style = { 
                    { Attribute::COLOR, Rgb() },
                    { Attribute::SIZE,  Size() },
                    { Attribute::POSITION, Position() }
                };
            public:
                Style();
                Style(StyleArg style);
                
                Style& operator=(const Style &other);
                Style& operator=(const StyleArg &other);
                
                void updateStyle(Attribute key, StyleVariant value);
                void updateStyle(StyleArg style);
                void updateStyle(Style style);

                Rgb getColor(){ return _color; }
                Size getSize(){ return _size; }
                Position getPosition(){ return _position; }
                StyleArg getAllStyles(){ return _style; }
                
                template<typename T> 
                T getOneStyle(Attribute key){ return std::get<T>(_style.at(key)); }
        };
   }
#endif