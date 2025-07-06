#pragma once

#include <array>
#include <glm/glm.hpp>
#include <vector>

namespace sdlk
{
	using point = std::array<float, 2>;
	using ring = std::vector<point>;

	class polygon
	{
	private:
		std::vector<ring> m_data;

	public:
		polygon() = default;
		explicit polygon(ring outer, std::vector<ring> holes = {});

		[[nodiscard]] auto outer() const -> const ring &;
		[[nodiscard]] auto holes() const -> std::vector<ring>;
		[[nodiscard]] auto ring_count() const -> int;
		[[nodiscard]] auto get_ring(int index) const -> const ring &;
		[[nodiscard]] auto data() const -> const std::vector<ring> &;
		[[nodiscard]] auto flattened() const -> std::vector<point>;
		[[nodiscard]] auto flattened_as_ndc(const int &window_width, const int &window_height) const
			-> std::vector<glm::vec2>;
	};
}  // namespace sdlk
