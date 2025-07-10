#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/types.hpp>
#include <stdexcept>

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

	auto polygon::data() const -> const std::vector<ring>&
	{
		return m_data;
	}

	auto polygon::data_as_float() const -> std::vector<std::vector<std::array<float, 2>>>
	{
		std::vector<std::vector<std::array<float, 2>>> result;
		result.reserve(m_data.size());

		for (const auto& ring : m_data)
		{
			std::vector<std::array<float, 2>> ring_converted;
			ring_converted.reserve(ring.size());

			for (const auto& point : ring)
			{
				ring_converted.push_back({ point.x, point.y });
			}

			result.push_back(std::move(ring_converted));
		}

		return std::move(result);
	}

	auto polygon::flattened() const -> std::vector<glm::vec2>
	{
		std::vector<glm::vec2> result;
		for (const auto& r : m_data)
		{
			result.insert(result.end(), r.begin(), r.end());
		}
		return result;
	}
}  // namespace sdlk
