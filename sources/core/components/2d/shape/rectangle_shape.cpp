//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/components/2d/shape/rectangle_shape.hpp>
#include <sdlk/core/components/2d/type.hpp>

namespace sdlk2d
{
	static auto to_points(const type::point &origin, float width, float height)
		-> std::vector<type::point>;

	rectangle_shape::rectangle_shape(const type::point &origin,
		const float &width,
		const float &height,
		const SDL_Color &color)
		: polygon_shape(to_points(origin, width, height), color)
	{
	}

	static auto to_points(const type::point &origin, float width, float height)
		-> std::vector<type::point>
	{
		const float x0 = origin.x;
		const float y0 = origin.y;
		const float x1 = origin.x + width;
		const float y1 = origin.y - height;

		return {
			{ x0, y0 },
			{ x1, y0 },
			{ x1, y1 },

			{ x0, y0 },
			{ x1, y1 },
			{ x0, y1 },
		};
	}
}  // namespace sdlk2d
