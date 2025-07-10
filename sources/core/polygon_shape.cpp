#include <mapbox/earcut.hpp>
#include <sdlk/core/app.hpp>
#include <sdlk/core/shape.hpp>

namespace sdlk
{
	polygon_shape::polygon_shape(polygon polygon)
		: shape(polygon.flattened(), mapbox::earcut(polygon.data_as_float())) { };
}
