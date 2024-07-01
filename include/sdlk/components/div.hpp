#pragma once

#include <sdlk/core/component.hpp>

namespace sdlk
{
	class Div : public Component
	{
	protected:
		virtual void clean_texture(SDL_Renderer *renderer) override;

	public:
		Div(Component *parent, Size size, Position position = Position());
	};
}  // namespace sdlk
