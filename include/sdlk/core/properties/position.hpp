#pragma once

#include <sdlk/core/preprocessor/data_definition.hpp>
#include <sdlk/core/preprocessor/getter_setter.hpp>

namespace sdlk
{
	class Position
	{
	protected:
		int m_x = 0, m_y = 0;

	public:
		GETTER_SETTER(int, x)
		GETTER_SETTER(int, y)

		Position(int x, int y);
		Position(int xy);

		DATA_DEFINITION(Position)
	};
}  // namespace sdlk
