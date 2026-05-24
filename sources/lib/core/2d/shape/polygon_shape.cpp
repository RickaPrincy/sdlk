//
// Created by ricka on 2025-12-31.
//

#include <array>
#include <sdlk/core/geometry.hpp>
#include <sdlk/core/gl/gl_program.hpp>
#include <sdlk/core/2d/shape/polygon_shape.hpp>

namespace sdlk2d
{
	static auto map_vertices(const type::polygon& polygon) -> std::vector<std::array<float, 9>>;

	polygon_shape::polygon_shape(const type::polygon& polygon)
	{
		const auto data = map_vertices(polygon);

		auto vao = std::make_unique<sdlk::gl_vertex_array>();
		auto vbo = std::make_unique<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();

		vao->enable_attrib(0);	// position
		vao->enable_attrib(1);	// color
	    vao->enable_attrib(2);	// uv

        constexpr GLsizei stride = sizeof(data[0]);
		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, stride, nullptr);  // position
		vao->attrib_pointer(1,
			4,
			GL_FLOAT,
			GL_FALSE,
            stride,
			reinterpret_cast<void*>(3 * sizeof(float)));  // color
	    vao->attrib_pointer(2,
            2,
            GL_FLOAT,
            GL_FALSE,
            stride,
            reinterpret_cast<void*>((3 + 4) * sizeof(float)));  // uv

		vbo->set_data(data.data(), GL_STATIC_DRAW, data.size(), stride);

		vbo->unbind();
		vao->unbind();

		this->m_geometry = std::make_unique<sdlk::geometry>(std::move(vao), std::move(vbo), nullptr);
	}

	auto polygon_shape::render(const std::shared_ptr<sdlk::gl_program>& program) -> void
	{
		renderable::render(program);
	}

	static auto map_vertices(const type::polygon& polygon) -> std::vector<std::array<float, 9>>
	{
		std::vector<std::array<float, 9>> result{};
		result.reserve(polygon.size());

		for (const auto&[m_uv, m_position, m_color] : polygon)
		{
			const auto ndc_color = m_color.ndc();
			result.push_back({
			    m_position.x, m_position.y, 0.0f /* z = 0 for now */,
				ndc_color.r,  ndc_color.g, ndc_color.b,  ndc_color.a,
			    m_uv.x,       m_uv.y
			});
		}
		return result;
	}
}  // namespace sdlk2d
