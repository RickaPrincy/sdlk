#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <sdlk/components/text.hpp>
#include <sdlk/utils/basic_wrapper.hpp>
#include <stdexcept>

sdlk::Text::Text(sdlk::Component *parent,
	std::string text_content,
	SDL_Color color,
	TTF_Font *font_family,
	sdlk::Position position)
	: sdlk::TexturedComponent(parent, Size(), position),
	  m_color(color),
	  p_font_family(font_family),
	  m_text_content(text_content)
{
}

void sdlk::Text::re_create_texture(SDL_Renderer *renderer)
{
	if (m_do_re_render)
	{
		if (sdlk::check::is_null(p_font_family))
		{
			throw std::runtime_error("Cannot render text when font is null");
		}

		SDL_Surface *text_surface = TTF_RenderText_Solid(p_font_family, m_text_content.c_str(), m_color);
		this->set_size(Size(text_surface->w, text_surface->h));
		p_loaded_text = SDL_CreateTextureFromSurface(renderer, text_surface);
		SDL_FreeSurface(text_surface);

		if (sdlk::check::is_null(p_loaded_text))
		{
			throw std::runtime_error("Cannot create loaded text");
		}
	}

	if (sdlk::check::is_null(p_sdl_texture))
	{
		SDL_DestroyTexture(p_sdl_texture);
	}
	this->p_sdl_texture = sdlk::create_target_texture(renderer, p_loaded_text, this->get_width(), this->get_height());
}

sdlk::Text::~Text()
{
	if (sdlk::check::is_null(p_font_family))
	{
		TTF_CloseFont(p_font_family);
	}

	if (sdlk::check::is_null(p_loaded_text))
	{
		SDL_DestroyTexture(p_loaded_text);
	}
}
