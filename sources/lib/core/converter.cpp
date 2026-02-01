#include <sdlk/core/converter.hpp>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(const SDL_Color &color) -> glm::vec4
	{
		return { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
	}
}  // namespace sdlk::converter
