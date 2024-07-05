#include <SDL2/SDL_image.h>

#include <sdlk/components/image.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Image::Image(sdlk::Component *parent, std::string src, sdlk::Size size, sdlk::Position position)
	: sdlk::Component(parent, size, position),
	  m_src(src)
{
}

sdlk::Image::~Image()
{
	if (!sdlk::check::is_null(p_loaded_image))
	{
		SDL_FreeSurface(p_loaded_image);
	}
}

void sdlk::Image::clean_texture(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(p_loaded_image))
	{
		p_loaded_image = IMG_Load(m_src.c_str());
		if (sdlk::check::is_null(p_loaded_image))
		{
			throw std::runtime_error("Cannot create texture surface");
		}
	}

	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}

	p_sdl_texture = SDL_CreateTextureFromSurface(renderer, p_loaded_image);
}
