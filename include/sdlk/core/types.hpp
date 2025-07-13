#pragma once

#include <array>
#include <vector>

namespace sdlk
{
	using point = std::array<float, 2>;
	using ring = std::vector<point>;

	class polygon
	{
	private:
		std::vector<ring> m_data{};

	public:
		polygon() = default;
		explicit polygon(ring outer, std::vector<ring> holes = {});

		[[nodiscard]] auto data() const -> const std::vector<ring> &;
		[[nodiscard]] auto flattened() const -> std::vector<point>;
	};
}  // namespace sdlk
