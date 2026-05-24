//
// Created by ricka on 2026-01-18.
//

#pragma once

#include <sdlk/core/2d/shape/polygon_shape.hpp>

namespace sdlk2d
{
	class rectangle_shape : public polygon_shape
	{
	public:
		rectangle_shape(const type::point &origin, const float &width, const float &height);

	    ~rectangle_shape() override = default;
	};
}  // namespace sdlk2d
