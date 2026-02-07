//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <sdlk/core/color.hpp>
#include <sdlk/core/components/2d/shape/shape_style.hpp>
#include <sdlk/core/components/2d/type.hpp>
#include <sdlk/core/components/renderable.hpp>
#include <sdlk/core/gl/gl_texture.hpp>

namespace sdlk2d
{
	class polygon_shape : public sdlk::renderable
	{
		shape_style m_style{};

	public:
		explicit polygon_shape(const type::polygon &polygon);
		explicit polygon_shape(const type::points &points, const sdlk::color &uniform_color);
		explicit polygon_shape(const type::polygon &polygon, const sdlk::color &uniform_color);

		explicit polygon_shape(const type::polygon &polygon,
			const std::shared_ptr<sdlk::gl_texture> &texture);

		auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;

		~polygon_shape() override = default;
	};
}  // namespace sdlk2d