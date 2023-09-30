#ifndef __SDLK_BOX__
#define __SDLK_BOX__

    #include "../components/component.hpp"
    
    namespace Sdlk{
        class Box : public Component{
            public:
                Box(Style style): Component(style){};
                Box(StyleArg style): Component(style){};
                Box():Component(){};
                ~Box(){};

                //overrided function
                void render(SDL_Renderer *renderer) override{
                    Rgb color; 
                    Size size; 
                    color = getStyle(Attribute::COLOR);
                    size = getStyle(Attribute::SIZE);

                    if(Check::isNull(_texture)){
                        _texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size._w,size._h);
                        if (Check::isNull(_texture)){
                            Program::exit(ExitStatus::FAILURE, "Cannot create a texture");
                            return;
                        }
                        Utils::setRenderColor(renderer,color);
                        Utils::setRenderTarget(renderer,_texture);
                        Utils::clearRenderer(renderer);
                        Utils::setRenderTarget(renderer,NULL);
                    }
                    
                    Component::render(renderer);
                }
        };
    }
#endif