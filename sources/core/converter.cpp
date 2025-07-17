#include <array>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/types.hpp>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>
	{
		return { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
	}

	auto pixel_uv_to_ndc(std::vector<point> pixels, int texture_width, int texture_height)
		-> std::vector<point>
	{
		std::vector<point> uv_coords;
		uv_coords.reserve(pixels.size());

		for (const auto& p : pixels)
		{
			float u = p[0] / static_cast<float>(texture_width);
			float v = p[1] / static_cast<float>(texture_height);
			uv_coords.push_back({ u, v });
		}

		return uv_coords;
	}
}  // namespace sdlk::converter
