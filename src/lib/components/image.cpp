#include <SDL2/SDL_image.h>

#include <sdlk/components/image.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Image::Image(sdlk::Component *parent, std::string src, sdlk::Size size, sdlk::Position position)
	: sdlk::TexturedComponent(parent, size, position),
	  m_src(src)
{
}

sdlk::Image::~Image()
{
	if (!sdlk::check::is_null(p_loaded_image))
	{
		SDL_DestroyTexture(p_loaded_image);
	}
}

void sdlk::Image::re_create_texture(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(p_loaded_image))
	{
		SDL_Surface *loaded_image_surface = IMG_Load(m_src.c_str());
		if (sdlk::check::is_null(loaded_image_surface))
		{
			throw std::runtime_error("Cannot create texture surface");
		}
		p_loaded_image = SDL_CreateTextureFromSurface(renderer, loaded_image_surface);
		SDL_FreeSurface(loaded_image_surface);
		if (sdlk::check::is_null(p_loaded_image))
		{
			throw std::runtime_error("Cannot create texture");
		}
	}

	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}

	p_sdl_texture = sdlk::create_target_texture(renderer, p_loaded_image, this->get_width(), this->get_height());
}
