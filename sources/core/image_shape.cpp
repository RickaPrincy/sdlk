#include <sdlk/core/app.hpp>
#include <sdlk/core/converter.hpp>
#include <sdlk/core/quad.hpp>
#include <sdlk/core/shape.hpp>
#include <sdlk/core/texture.hpp>
#include <sdlk/core/types.hpp>
#include <vector>

namespace sdlk
{
	image_shape::image_shape(std::string image_path, int width, int height)
		: textured_shape(std::move(polygon(quad::make(std::move(width), std::move(height)))),
			  std::move(quad::uv()),
			  std::move(texture::from_file(std::move(image_path))),
			  std::move(quad::indices()))
	{
	}
}  // namespace sdlk
