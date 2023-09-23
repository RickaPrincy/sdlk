#ifndef __SDLK_BOX__
#define __SDLK_BOX__

    #include "../components/component.hpp"
    
    namespace Sdlk{
        class Box : public Component{
            public:
                Box(Size size, Position position = Position(0)): Component(size,position){};
                Box():Component(){};
                ~Box(){};

                //overrided function
                void render(SDL_Renderer *renderer) override{
                    if(Check::isNull(_texture)){
                        _texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _size._w,_size._h);
                        if (Check::isNull(_texture)){
                            Program::exit(ExitStatus::FAILURE, "Cannot create a texture");
                            return;
                        }
                        Utils::setRenderColor(renderer,_color);
                        Utils::setRenderTarget(renderer,_texture);
                        Utils::clearRenderer(renderer);
                        Utils::setRenderTarget(renderer,NULL);
                    }
                    
                    Component::render(renderer);
                }
        };
    }
#endif