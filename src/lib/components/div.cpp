#include <sdlk/components/div.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Div::Div(sdlk::Component *parent, sdlk::Size size, sdlk::Position position)
	: sdlk::Component(parent, size, position)
{
}

void sdlk::Div::clean_texture(SDL_Renderer *renderer)
{
	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}

	p_sdl_texture = SDL_CreateTexture(
		renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, m_size.get_width(), m_size.get_height());

	if (sdlk::check::is_null(p_sdl_texture))
	{
		throw std::runtime_error("Texture creation failed");
	}

	if (!sdlk::check::is_success(SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255)) ||
		!sdlk::check::is_success(SDL_SetRenderTarget(renderer, p_sdl_texture)) ||
		!sdlk::check::is_success(SDL_RenderClear(renderer)) ||
		!sdlk::check::is_success(SDL_SetRenderTarget(renderer, NULL)))
	{
		throw std::runtime_error("Texture creation failed for a div");
	}
}
