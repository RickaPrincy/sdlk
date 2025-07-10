#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <sdlk/core/renderable.hpp>
#include <sdlk/core/types.hpp>

namespace sdlk
{
	class shape : public renderable
	{
	protected:
		unsigned int m_indices_count{};

		GLuint m_vao{}, m_vbo{}, m_ebo{};

	public:
		shape(std::vector<glm::vec2> vertices, std::vector<uint32_t> indices);

		virtual auto bind() -> void const;

		virtual auto render(GLuint *program) -> void override;

		~shape();
	};

	class polygon_shape : public shape
	{
	protected:
		polygon m_polygon{};

	public:
		polygon_shape(polygon polygon);
	};
}  // namespace sdlk
