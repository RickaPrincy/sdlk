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
            public:
                StyleArg _style = { 
                    { Attribute::COLOR, "r:0, g:0, b:0" },
                    { Attribute::SIZE,  "w:10, h:10" },
                    { Attribute::POSITION, "x:0, y:0" }
                };
                
                StyleVariant getStyle(Attribute key);
                Style(){}
                Style(StyleArg style);

                void updateStyle(StyleArg style);
                void updateStyle(Style style);

                Style& operator=(const Style &other);
                Style& operator=(const StyleArg &other);
        };
   }
#endif