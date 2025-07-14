#pragma once

#include <SDL2/SDL_pixels.h>

#include <array>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>;
}  // namespace sdlk::converter
