#include <sdlk/core/types.hpp>
#include <stdexcept>
#include <string>

#include "utils.hpp"

namespace sdlk
{
	polygon::polygon(ring outer, std::vector<ring> holes)
	{
		holes.insert(holes.begin(), outer);

		if (holes.empty())
		{
			throw std::runtime_error("Polygon requires at least one ring (outer)");
		}
		m_data = std::move(holes);
	}

	auto polygon::outer() const -> const ring&
	{
		return m_data[0];
	}

	auto polygon::holes() const -> std::vector<ring>
	{
		return std::vector<ring>(m_data.begin() + 1, m_data.end());
	}

	auto polygon::ring_count() const -> int
	{
		return static_cast<int>(m_data.size());
	}

	auto polygon::get_ring(int index) const -> const ring&
	{
		if (index < 0 || index >= static_cast<int>(m_data.size()))
		{
			throw std::out_of_range("Ring index out of bounds: " + std::to_string(index));
		}
		return m_data[index];
	}

	auto polygon::data() const -> const std::vector<ring>&
	{
		return m_data;
	}

	auto polygon::flattened() const -> std::vector<point>
	{
		std::vector<point> result;
		for (const auto& r : m_data)
		{
			result.insert(result.end(), r.begin(), r.end());
		}
		return result;
	}

	auto polygon::flattened_as_ndc(const int& window_width, const int& window_height) const
		-> std::vector<glm::vec2>
	{
		const auto flat = this->flattened();

		std::vector<glm::vec2> pixels;
		pixels.reserve(flat.size());
		for (const auto& pt : flat)
		{
			pixels.emplace_back(glm::vec2{ pt[0], pt[1] });
		}

		return pixels_position_to_ndc(pixels, window_width, window_height);
	}
}  // namespace sdlk
