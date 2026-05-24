//
// Created by ricka on 2025-12-31.
//

#pragma once

#include <sdlk/core/2d/type.hpp>
#include <sdlk/core/2d/shape/shape.hpp>

namespace sdlk2d
{
	class polygon_shape : public shape
	{
	public:
		explicit polygon_shape(const type::polygon &polygon);

		auto render(const std::shared_ptr<sdlk::gl_program> &program) -> void override;

		~polygon_shape() override = default;
	};
}  // namespace sdlk2d