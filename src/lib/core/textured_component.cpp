#include <sdlk/core/textured_component.hpp>
#include <sdlk/utils/basic_wrapper.hpp>

sdlk::TexturedComponent::TexturedComponent(sdlk::Component *parent, sdlk::Size size, sdlk::Position position)
	: sdlk::Component(parent, size, position)
{
}

sdlk::TexturedComponent::~TexturedComponent()
{
	if (!sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}
}

void sdlk::TexturedComponent::render(SDL_Renderer *renderer)
{
	if (m_do_re_render)
	{
		this->re_create_texture(renderer);
		sdlk::throw_if_not_success(
			SDL_SetRenderTarget(renderer, p_sdl_texture), "Cannot set renderer target to textured_component");
		Component::render(renderer);
	}

	sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, NULL), "Cannot reset renderer target");
	if (!sdlk::check::is_null(p_parent))
	{
		if (auto parent = dynamic_cast<TexturedComponent *>(p_parent))
		{
			sdlk::throw_if_not_success(
				SDL_SetRenderTarget(renderer, parent->p_sdl_texture), "Cannot set renderer target to parent");
		}
	}

	SDL_Rect rect = { this->get_x(), this->get_y(), this->get_width(), this->get_height() };
	sdlk::throw_if_not_success(
		SDL_RenderCopy(renderer, p_sdl_texture, p_src_rect, &rect), "Cannot copy textured component to the target");
	sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, NULL), "Cannot reset render target");
}
