#pragma once

#include <sdlk/core/component.hpp>

namespace sdlk
{
	class Square : public Component
	{
	public:
		virtual void render(SDL_Renderer *renderer) override;
		Square(Size size, Position position = Position());
	};
}  // namespace sdlk
