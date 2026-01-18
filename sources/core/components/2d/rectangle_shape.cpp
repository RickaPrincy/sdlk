//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/components/2d/rectangle_shape.hpp>
#include <sdlk/core/components/2d/type.hpp>

namespace sdlk2d
{
	static auto to_polygon(const type::point &origin, float width, float height) -> type::polygon;

	rectangle_shape::rectangle_shape(const type::point &origin, float width, float height): polygon_shape(to_polygon(origin, width, height))
	{}

	static auto to_polygon(const type::point &origin, float width, float height) -> type::polygon {
		const float x0 = origin.x;
		const float y0 = origin.y;
		const float x1 = origin.x + width;
		const float y1 = origin.y - height;

		return {
	        {x0, y0},
			{x1, y0},
			{x1, y1},

			{x0, y0},
			{x1, y1},
			{x0, y1},
		};
	}
}  // namespace sdlk
