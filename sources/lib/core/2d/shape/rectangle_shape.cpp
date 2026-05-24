//
// Created by ricka on 2026-01-18.
//

#include <sdlk/core/2d/shape/rectangle_shape.hpp>
#include <sdlk/core/2d/type.hpp>

namespace sdlk2d
{
	static auto to_polygon(const type::point &origin, const float &width, const float &height) -> type::polygon;

	rectangle_shape::rectangle_shape(const type::point &origin, const float &width, const float &height)
		: polygon_shape(to_polygon(origin, width, height))
	{
	}

	static auto to_polygon(const type::point &origin, const float &width, const float &height)
		-> type::polygon
	{
		const float x0 = origin.x;
		const float y0 = origin.y;
		const float x1 = origin.x + width;
		const float y1 = origin.y + height;

	    return {
	        type::vertex{
                .m_uv = type::point{0.0f, 0.0f},
	            .m_position = type::point{x0, y0}
	        },
            type::vertex{
                .m_uv = type::point{1.0f, 0.0f},
                .m_position = type::point{x1, y0}
            },
            type::vertex{
                .m_uv = type::point{1.0f, 1.0f},
                .m_position = type::point{x1, y1}
            },
            type::vertex{
                .m_uv = type::point{0.0f, 0.0f},
                .m_position = type::point{x0, y0}
            },
            type::vertex{
                .m_uv = type::point{1.0f, 1.0f},
                .m_position = type::point{x1, y1}
            },
            type::vertex{
                .m_uv = type::point{0.0f, 1.0f},
                .m_position = type::point{x0, y1}
            }
	    };
	}
}  // namespace sdlk2d
