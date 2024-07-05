#pragma once

#include <SDL2/SDL_ttf.h>

#include <sdlk/core/component.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <string>

namespace sdlk
{
	class Text : public Component
	{
	protected:
		SDL_Surface *p_loaded_image = nullptr;	// to avoid a loading image again and again on update...
		TTF_Font *p_font_family = nullptr;
		SDL_Color m_color = { 0, 0, 0 };
		std::string m_text_content{};

		virtual void clean_texture(SDL_Renderer *renderer) override;

	public:
		Text(Component *parent,
			std::string text_content,
			SDL_Color color,
			TTF_Font *font_family,
			Position position = Position());
		virtual ~Text();
	};
}  // namespace sdlk
