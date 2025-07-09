#include <algorithm>
#include <iterator>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk::converter
{
	auto pixel_position_to_ndc(const glm::vec2 &pixel,
		const int &window_width,
		const int &window_height) -> glm::vec2
	{
		float x_ndc = (pixel.x / window_width) * 2.0f - 1.0f;
		float y_ndc = 1.0f - (pixel.y / window_height) * 2.0f;
		return { x_ndc, y_ndc };
	}

	auto pixels_position_to_ndc(const std::vector<glm::vec2> &pixels,
		const int &window_width,
		const int &window_height) -> std::vector<glm::vec2>
	{
		std::vector<glm::vec2> result{};

		result.reserve(pixels.size());

		std::transform(pixels.begin(),
			pixels.end(),
			std::back_inserter(result),
			[&](const glm::vec2 &vertex)
			{ return pixel_position_to_ndc(vertex, window_width, window_height); });

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
