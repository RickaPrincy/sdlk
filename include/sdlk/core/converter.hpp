#pragma once

#include <SDL2/SDL_pixels.h>
#include <glm/vec4.hpp>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(const SDL_Color &color) -> glm::vec4;
}  // namespace sdlk::converter
