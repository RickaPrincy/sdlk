//
// Created by ricka on 2025-12-31.
//

#include <sdlk/core/components/2d/polygon_shape.hpp>
#include <sdlk/core/geometry.hpp>
#include <sdlk/core/gl/gl_program.hpp>

#include "mapper_to_3d.hpp"

namespace sdlk2d
{
	polygon_shape::polygon_shape(const type::polygon& polygon)
	{
		const auto polygon3d = mapper_to_3d::map(polygon);

		auto vao = std::make_shared<sdlk::gl_vertex_array>();
		auto vbo = std::make_shared<sdlk::gl_buffer>(GL_ARRAY_BUFFER);

		vao->bind();
		vbo->bind();
		vao->enable_attrib(0);
		vao->attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		vbo->set_data(polygon3d.data(), GL_STATIC_DRAW, polygon3d.size(), sizeof(sdlk3d::type::point));
		vbo->unbind();
		vao->unbind();

		this->m_geometry = std::make_shared<sdlk::geometry>(vao, vbo, nullptr);
	}

	auto polygon_shape::render(const std::shared_ptr<sdlk::gl_program>& program) -> void
	{
		renderable::render(program);
	}
}  // namespace sdlk
