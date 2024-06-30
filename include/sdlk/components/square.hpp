#pragma once

#include <sdlk/core/component.hpp>

namespace sdlk
{
	class Square : public Component
	{
	protected:
		virtual void render(SDL_Renderer *renderer) override;

	public:
		Square(Component *parent, Size size, Position position = Position());
	};
}  // namespace sdlk
