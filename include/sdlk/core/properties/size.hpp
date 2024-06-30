#pragma once

#include <sdlk/core/preprocessor/data_definition.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>

namespace sdlk
{
	class Size
	{
	protected:
		int m_width = 10, m_height = 10;

	public:
		GETTER_SETTER(int, width)
		GETTER_SETTER(int, height)

		Size(int w, int h);
		Size(int wh);
		DATA_DEFINITION(Size)
	};
}  // namespace sdlk
