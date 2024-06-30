#include <SDL2/SDL_render.h>

#include <iostream>
#include <sdlk/core/renderable.hpp>
#include <stdexcept>

#include "../utils/check.hpp"

sdlk::Renderable::Renderable(SDL_Texture *texture)
{
	if (sdlk::check::is_null(texture))
	{
		throw std::runtime_error("texture cannot be null");
	}
	p_sdl_texture = texture;
}

void sdlk::Renderable::render(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(p_sdl_texture) || sdlk::check::is_null(renderer))
	{
		throw std::runtime_error("texture and renderer cannot be null");
	}

	SDL_Rect rect = { this->get_x(), this->get_y(), this->get_width(), this->get_height() };
	if (SDL_RenderCopy(renderer, p_sdl_texture, NULL, &rect) != 0)
	{
		throw std::runtime_error("Error occured when try to render a Renderable");
	}
}

sdlk::Renderable::~Renderable()
{
	std::cout << "Destroy texture" << std::endl;
	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}
}
