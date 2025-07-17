#include <sdlk/core/quad.hpp>

namespace sdlk::quad
{
	auto make(int width, int height) -> std::vector<point>
	{
		auto f_width = (float)width;
		auto f_height = (float)height;
		return { { 0, 0 }, { f_width, 0 }, { f_width, f_height }, { 0, f_height } };
	}

	auto indices() -> std::vector<uint32_t>
	{
		return { 0, 1, 2, 2, 3, 0 };
	}
}  // namespace sdlk::quad
