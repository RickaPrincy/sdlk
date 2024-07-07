#pragma once

#include <sdlk/core/preprocessor/getter_setter.hpp>
#include <sdlk/core/textured_component.hpp>
#include <string>

namespace sdlk
{
	class Image : public TexturedComponent
	{
	protected:
		SDL_Surface *p_loaded_image = nullptr;	// to avoid a loading image again and again on update...
		std::string m_src{};

		virtual void re_create_texture(SDL_Renderer *renderer) override;

	public:
		GETTER(std::string, src)

		Image(Component *parent, std::string src, Size size, Position position = Position());
		virtual ~Image();
	};
}  // namespace sdlk
