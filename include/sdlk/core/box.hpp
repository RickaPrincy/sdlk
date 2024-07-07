#pragma once

#include <sdlk/core/preprocessor/data_definition.hpp>
#include <sdlk/core/properties/position.hpp>
#include <sdlk/core/properties/size.hpp>

namespace sdlk
{
	class Box
	{
	protected:
		Size m_size;
		Position m_position;

	public:
		GETTER_SETTER(Position, position)
		GETTER_SETTER(Size, size)

		virtual int get_x() const;
		virtual int get_y() const;
		virtual int get_width() const;
		virtual int get_height() const;

		virtual void set_x(int x);
		virtual void set_y(int y);
		virtual void set_width(int width);
		virtual void set_height(int width);

		Box(Size size);
		Box(Size size, Position position);
		Box(int width, int height, int x, int y);
		DATA_DEFINITION(Box)
	};
}  // namespace sdlk
