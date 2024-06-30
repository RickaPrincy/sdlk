#include <sdlk/components/square.hpp>
#include <stdexcept>

#include "../utils/check.hpp"

void sdlk::Square::render(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(this->p_sdl_texture))
	{
		p_sdl_texture = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_size.get_width(), m_size.get_height());

		if (sdlk::check::is_null(p_sdl_texture))
		{
			throw std::runtime_error("Texture creation failed");
		}
	}

	if (m_should_renderer_childs)
	{
		if (SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255) != 0 ||
			SDL_SetRenderTarget(renderer, p_sdl_texture) != 0 || SDL_RenderClear(renderer) != 0 ||
			SDL_SetRenderTarget(renderer, NULL) != 0)
		{
			throw std::runtime_error("render color failed");
		}
	}

	Component::render(renderer);
}

sdlk::Square::Square(sdlk::Component *parent, sdlk::Size size, sdlk::Position position)
	: sdlk::Component(parent, size, position)
{
}
