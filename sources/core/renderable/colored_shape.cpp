//
// Created by ricka on 2025-12-31.
//

#include <sdlk/core/geometry.hpp>
#include <sdlk/core/renderable/colored_shape.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/gl/gl_program.hpp>

//TODO: review and refactor color_shape
namespace sdlk
{
	colored_shape::colored_shape(const type::polygon& polygon, const SDL_Color color)
	{
		auto vao = std::make_shared<gl_vertex_array>();
		auto vbo = std::make_shared<gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vao->enable_attrib(0);
		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		std::vector<float> vertices;
		vertices.reserve(polygon.size() * 3);

		for (const auto& vertex : polygon)
		{
			vertices.emplace_back(vertex.x);
			vertices.emplace_back(vertex.y);
			vertices.emplace_back(vertex.z);
		}

		vbo->set_data(vertices.data(), GL_STATIC_DRAW, vertices.size(), sizeof(float));
		vao->unbind();

		this->m_color = color;
		this->m_geometry = std::make_shared<geometry>(vao, vbo, nullptr);
	}

	auto colored_shape::render(const std::shared_ptr<gl_program>& program) -> void
	{
		const auto ndc_color= converter::sdl_color_to_ndc(this->m_color);
		const glm::vec3 u_color =  {ndc_color[0], ndc_color[1], ndc_color[2]};

		program->get_uniform()->set("u_color", u_color);

		renderable::render(program);
	}
}  // namespace sdlk
