#include <glad/glad.h>

#include <iostream>
#include <cstdint>
#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/opengl_utils.hpp>
#include <sdlk/core/shape.hpp>

namespace sdlk
{
	shape::shape(polygon polygon, std::vector<uint32_t> indices, shape_config config)
		: m_polygon(polygon),
		  m_config(std::move(config))
	{
		this->m_indices_count = static_cast<unsigned int>(indices.size());

		glGenVertexArrays(1, &this->m_vao);
		glGenBuffers(1, &this->m_vbo);
		glGenBuffers(1, &this->m_ebo);

		glBindVertexArray(this->m_vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(uint32_t),
			indices.data(),
			GL_STATIC_DRAW);
	}

	auto shape::bind() -> void const
	{
		renderable::bind();
		glBindVertexArray(this->m_vao);
	}

	auto shape::set_color(SDL_Color color) -> void
	{
		this->m_color = color;
		this->m_ndc_color = converter::sdl_color_to_ndc(std::move(color));
	}

	auto shape::render(GLuint *program) -> void
	{
		renderable::render(program);

		if (!this->m_indices_count)
		{
			return;
		}

		auto use_vec_color_loc = get_uniform_loc(program, "uUseVecColor");
		auto use_texture_loc = get_uniform_loc(program, "uUseTexture");
		auto use_text_rendering_loc = get_uniform_loc(program, "uUseTextRendering");
		auto u_color_loc = get_uniform_loc(program, "uColor");

		glUniform1i(use_vec_color_loc, this->m_config.use_vec_color ? 1 : 0);
		glUniform1i(use_texture_loc, this->m_config.use_texture ? 1 : 0);
		glUniform1i(use_text_rendering_loc, this->m_config.use_text_rendering ? 1 : 0);
		glUniform4fv(u_color_loc, 1, this->m_ndc_color.data());

		glDrawElements(GL_TRIANGLES, this->m_indices_count, GL_UNSIGNED_INT, 0);
	}

	auto shape::get_color() -> SDL_Color
	{
		return this->m_color;
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
