#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/shape.hpp>
#include <stdexcept>
#include <vector>

namespace sdlk
{
	static auto load_colored_vertices(GLuint *vao, GLuint *vbo, const std::vector<float> &vertices)
		-> void;

	colored_shape::colored_shape(polygon geometry, SDL_Color color)
		: colored_shape(geometry,
			  std::move(color),
			  std::move(mapbox::earcut(std::move(geometry.data()))))
	{
	}

	colored_shape::colored_shape(polygon geometry, SDL_Color color, std::vector<uint32_t> indices)
		: shape(std::move(geometry), std::move(indices), false)
	{
		auto positions = this->m_polygon.flattened();
		auto ndc_color = converter::sdl_color_to_ndc(std::move(color));

		std::vector<float> vertices{};
		for (size_t i = 0; i < positions.size(); i++)
		{
			vertices.push_back(positions[i][0]);
			vertices.push_back(positions[i][1]);
			vertices.push_back(ndc_color[0]);  // r
			vertices.push_back(ndc_color[1]);  // g
			vertices.push_back(ndc_color[2]);  // b
			vertices.push_back(ndc_color[3]);  // a
		}

		load_colored_vertices(&this->m_vao, &this->m_vbo, vertices);
	}

	colored_shape::colored_shape(polygon geometry, std::vector<SDL_Color> colors)
		: colored_shape(geometry,
			  std::move(colors),
			  std::move(mapbox::earcut(std::move(geometry.data()))))
	{
	}

	colored_shape::colored_shape(polygon geometry,
		std::vector<SDL_Color> colors,
		std::vector<uint32_t> indices)
		: shape(std::move(geometry), std::move(indices), false)
	{
		auto positions = this->m_polygon.flattened();
		if (positions.size() != colors.size())
		{
			throw std::runtime_error("Some colors are missing for vertex");
		}

		std::vector<float> vertices{};
		for (size_t i = 0; i < positions.size(); i++)
		{
			vertices.push_back(positions[i][0]);
			vertices.push_back(positions[i][1]);

			auto ndc_color = converter::sdl_color_to_ndc(std::move(colors[i]));
			vertices.push_back(ndc_color[0]);  // r
			vertices.push_back(ndc_color[1]);  // g
			vertices.push_back(ndc_color[2]);  // b
			vertices.push_back(ndc_color[3]);  // a
		}

		load_colored_vertices(&this->m_vao, &this->m_vbo, vertices);
	}

	static auto load_colored_vertices(GLuint *vao, GLuint *vbo, const std::vector<float> &vertices)
		-> void
	{
		glBindVertexArray(*vao);
		glBindBuffer(GL_ARRAY_BUFFER, *vbo);
		glBufferData(
			GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
		glEnableVertexAttribArray(0);

		glDisableVertexAttribArray(1);	// texture attribute

		glVertexAttribPointer(
			2, 4, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(2 * sizeof(float)));
		glEnableVertexAttribArray(2);

		glBindVertexArray(0);
	}

}  // namespace sdlk
