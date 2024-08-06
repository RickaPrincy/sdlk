#include <sdlk/core/textured_component.hpp>
#include <sdlk/utils/basic_wrapper.hpp>

sdlk::TexturedComponent::TexturedComponent(sdlk::Component *parent,
	sdlk::Size size,
	sdlk::Position position)
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
		sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, p_sdl_texture),
			"Cannot set target to texturedComponent it self");
		Component::render(renderer);
		sdlk::throw_if_not_success(
			SDL_SetRenderTarget(renderer, NULL), "Cannot reset target from component it self");
	}

	if (!sdlk::check::is_null(p_parent))
	{
		if (auto parent = dynamic_cast<TexturedComponent *>(p_parent))
		{
			sdlk::throw_if_not_success(SDL_SetRenderTarget(renderer, parent->p_sdl_texture),
				"Cannot set renderer target to textured_component");
		}
	}

	SDL_Rect rect = {
		m_real_position.get_x(), m_real_position.get_y(), this->get_width(), this->get_height()
	};
	bool copy_all_image = m_src_rect.w < 0 || m_src_rect.h < 0;
	sdlk::throw_if_not_success(
		SDL_RenderCopy(renderer, p_sdl_texture, copy_all_image ? NULL : &m_src_rect, &rect),
		"Cannot copy textured component to the target");
	sdlk::throw_if_not_success(
		SDL_SetRenderTarget(renderer, nullptr), "Cannot reset render target");
}
