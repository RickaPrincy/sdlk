#include <algorithm>
#include <array>
#include <iterator>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::converter
{
	auto sdl_color_to_ndc(SDL_Color color) -> std::array<float, 4>
	{
		return { color.r / 255.0f, color.g / 255.0f, color.b / 255.0f, color.a / 255.0f };
	}

	auto pixel_point_to_ndc(const point &pixel, const int &window_width, const int &window_height)
		-> point
	{
		float x_ndc = (pixel[0] / window_width) * 2.0f - 1.0f;
		float y_ndc = 1.0f - (pixel[1] / window_height) * 2.0f;
		return { x_ndc, y_ndc };
	}

	auto pixels_points_to_ndcs(const std::vector<point> &pixels,
		const int &window_width,
		const int &window_height) -> std::vector<point>
	{
		std::vector<point> result{};

		result.reserve(pixels.size());

		std::transform(pixels.begin(),
			pixels.end(),
			std::back_inserter(result),
			[&](const point &vertex)
			{ return pixel_point_to_ndc(vertex, window_width, window_height); });

		return result;
	}

	auto pixel_offset_to_ndc(const glm::vec2 &offset,
		const int &window_width,
		const int &window_height) -> glm::vec2
	{
		float x_ndc = offset.x / (window_width * 0.5f);
		float y_ndc = -offset.y / (window_height * 0.5f);
		return { x_ndc, y_ndc };
	}

	auto pixel_scale_to_ndc(const glm::vec2 &pixel, const int &width, const int &height)
		-> glm::vec2
	{
		return { pixel.x / static_cast<float>(width) * 2.0f,
			pixel.y / static_cast<float>(height) * 2.0f };
	}
}  // namespace sdlk::converter
