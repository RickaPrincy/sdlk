#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace sdlk
{
	using ring = std::vector<glm::vec2>;

	class polygon
	{
	private:
		std::vector<ring> m_data{};

	public:
		polygon() = default;
		explicit polygon(ring outer, std::vector<ring> holes = {});

		[[nodiscard]] auto data() const -> const std::vector<ring> &;
		[[nodiscard]] auto data_as_float() const -> std::vector<std::vector<std::array<float, 2>>>;
		[[nodiscard]] auto flattened() const -> std::vector<glm::vec2>;
	};
}  // namespace sdlk
