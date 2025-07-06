#include "utils.hpp"

#include <algorithm>
#include <iterator>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk
{
	auto pixel_to_ndc(const glm::vec2 &pixel, const int &window_width, const int &window_height)
		-> glm::vec2
	{
		float x_ndc = (pixel.x / window_width) * 2.0f - 1.0f;
		float y_ndc = 1.0f - (pixel.y / window_height) * 2.0f;
		return { x_ndc, y_ndc };
	}

	auto pixels_to_ndc(const std::vector<glm::vec2> &pixels,
		const int &window_width,
		const int &window_height) -> std::vector<glm::vec2>
	{
		std::vector<glm::vec2> result{};

		result.reserve(pixels.size());

		std::transform(pixels.begin(),
			pixels.end(),
			std::back_inserter(result),
			[&](const glm::vec2 &vertex)
			{ return pixel_to_ndc(vertex, window_width, window_height); });

		return result;
	}
}  // namespace sdlk
