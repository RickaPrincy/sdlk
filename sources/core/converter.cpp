#include <array>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/types.hpp>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>
	{
		return { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
	}
}  // namespace sdlk::converter
