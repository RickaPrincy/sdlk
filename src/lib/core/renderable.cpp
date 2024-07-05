#include <SDL2/SDL_render.h>

#include <sdlk/core/renderable.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Renderable::Renderable(sdlk::Size size, sdlk::Position position, SDL_Texture *texture) : sdlk::Box(size, position)
{
	p_sdl_texture = texture;
}

void sdlk::Renderable::render(SDL_Renderer *renderer)
{
	if (sdlk::check::is_null(p_sdl_texture) || sdlk::check::is_null(renderer))
	{
		throw std::runtime_error("texture and renderer cannot be null");
	}

	SDL_Rect rect = { this->get_x(), this->get_y(), this->get_width(), this->get_height() };
	sdlk::throw_if_not_success(
		SDL_RenderCopy(renderer, p_sdl_texture, p_src_rect, &rect), "Error occured when try to render a Renderable");
}

sdlk::Renderable::~Renderable()
{
	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}
}
