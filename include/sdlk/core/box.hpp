#include <sdlk/core/properties/position.hpp>
#include <sdlk/core/properties/size.hpp>

namespace sdlk
{
	class Box
	{
	public:
		Size m_size;
		Position m_position;

		virtual int get_x() const;
		virtual int get_y() const;
		virtual int get_width() const;
		virtual int get_height() const;

		virtual void set_x(int x);
		virtual void set_y(int y);
		virtual void set_width(int width);
		virtual void set_height(int width);

		Box() = default;
		Box(Size size, Position position);
		Box(Size size);
		Box(int width, int height, int x, int y);
	};
}  // namespace sdlk
