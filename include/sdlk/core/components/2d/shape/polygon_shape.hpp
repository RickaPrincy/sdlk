//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <sdlk/core/components/2d/shape/shape_style.hpp>
#include <sdlk/core/components/2d/type.hpp>
#include <sdlk/core/renderable/renderable.hpp>

namespace sdlk2d
{
	class polygon_shape : public sdlk::renderable
	{
		shape_style m_style{};

	public:
		explicit polygon_shape(const type::polygon &polygon);
		explicit polygon_shape(const std::vector<type::point> &points, const SDL_Color &uniform_color);
		explicit polygon_shape(const type::polygon &polygon, const SDL_Color &uniform_color);

		explicit polygon_shape(const type::polygon &polygon, const std::shared_ptr<texture> &texture);

		auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;

		~polygon_shape() override = default;
	};
}  // namespace sdlk2d