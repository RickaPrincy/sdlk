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

	auto polygon::flattened() const -> std::vector<point>
	{
		std::vector<point> result;
		for (const auto& r : m_data)
		{
			result.insert(result.end(), r.begin(), r.end());
		}
		return result;
	}
}  // namespace sdlk
