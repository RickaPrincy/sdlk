#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <vector>

namespace sdlk
{
	class component
	{
	protected:
		GLuint m_vao{}, m_vbo{};
		std::vector<glm::vec2> m_ndc_vertex{};
		component *p_parent = nullptr;

	private:
		glm::vec2 _window_size{};

	public:
		component(std::vector<glm::vec2> pixel_vertex, component *parent);
		component(std::vector<glm::vec2> pixel_vertex, const glm::vec2 &window_size);
		~component();

		auto draw() -> void const;
		auto append_child(component *component) -> void;
		friend class app;
	};
}  // namespace sdlk
