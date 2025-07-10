#include <glad/glad.h>

#include <iostream>
#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/shape.hpp>

namespace sdlk
{
	shape::shape(std::vector<glm::vec2> pixel_vertices, std::vector<uint32_t> indices)
	{
		auto vertices =
			converter::pixels_position_to_ndc(pixel_vertices, app::get_width(), app::get_height());

		this->m_indices_count = static_cast<unsigned int>(indices.size());

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
		glBufferData(
			GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec2), vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint32_t),
			indices.data(),
			GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *)0);
		glEnableVertexAttribArray(0);
		glBindVertexArray(0);
	}

	auto shape::bind() -> void const
	{
		glBindVertexArray(this->m_vao);
	}

	auto shape::render(GLuint *program) -> void
	{
		if (!this->m_indices_count)
		{
			return;
		}

		glDrawElements(GL_TRIANGLES, this->m_indices_count, GL_UNSIGNED_INT, 0);
	}

	shape::~shape()
	{
		if (this->m_ebo)
		{
			glDeleteBuffers(1, &m_ebo);
		}

		if (this->m_vbo)
		{
			glDeleteBuffers(1, &m_vbo);
		}

		if (this->m_vao)
		{
			glDeleteVertexArrays(1, &m_vao);
		}
		std::cout << "clean shape\n";
	}
}  // namespace sdlk
