#include <cstdint>
#include <mapbox/earcut.hpp>
#include <memory>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/opengl_utils.hpp>
#include <sdlk/core/quad.hpp>
#include <sdlk/core/shape.hpp>
#include <stdexcept>

namespace sdlk
{
	static auto load_textured_vertices(GLuint *vao, GLuint *vbo, const std::vector<float> &vertices)
		-> void;

	textured_shape::textured_shape(polygon geometry,
		std::vector<point> uv,
		std::shared_ptr<texture> texture)
		: textured_shape(geometry,
			  std::move(uv),
			  std::move(texture),
			  std::move(mapbox::earcut(geometry.data())))
	{
	}

	textured_shape::textured_shape(polygon geometry,
		std::vector<point> uv,
		std::shared_ptr<texture> texture,
		std::vector<uint32_t> indices)
		: shape(std::move(geometry), std::move(indices), { false, true, false }),
		  m_texture(std::move(texture))
	{
		auto positions = this->m_polygon.flattened();
		if (positions.size() != uv.size())
		{
			throw std::runtime_error("Some uv are missing for vertex");
		}

		std::vector<float> vertices{};
		auto ndc_uv = converter::pixel_uv_to_ndc(
			uv, this->m_texture->get_width(), this->m_texture->get_height());
		for (size_t i = 0; i < positions.size(); i++)
		{
			vertices.push_back(positions[i][0]);
			vertices.push_back(positions[i][1]);
			vertices.push_back(ndc_uv[i][0]);
			vertices.push_back(ndc_uv[i][1]);
		}

		load_textured_vertices(&this->m_vao, &this->m_vbo, vertices);
	}

	auto textured_shape::bind() -> const void
	{
		shape::bind();
		this->m_texture->bind(0);  // TODO: handle texture unit
	}

	auto textured_shape::render(GLuint *program) -> void
	{
		auto u_texture_loc = get_uniform_loc(program, "uTexture");
		glUniform1i(u_texture_loc, 0);	// TODO: handle texture unit

		shape::render(program);
	}

	static auto load_textured_vertices(GLuint *vao, GLuint *vbo, const std::vector<float> &vertices)
		-> void
	{
		glBindVertexArray(*vao);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBufferData(
			GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glDisableVertexAttribArray(2);	// for color texture
		glBindVertexArray(0);
	}
}  // namespace sdlk
