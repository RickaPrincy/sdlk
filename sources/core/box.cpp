#include <sdlk/core/box.hpp>

int sdlk::Box::get_x() const
{
	return m_position.get_x();
};

int sdlk::Box::get_y() const
{
	return m_position.get_y();
};

int sdlk::Box::get_width() const
{
	return m_size.get_width();
};

int sdlk::Box::get_height() const
{
	return m_size.get_height();
};

void sdlk::Box::set_x(int x)
{
	m_position.set_x(x);
};

void sdlk::Box::set_y(int y)
{
	m_position.set_y(y);
};

void sdlk::Box::set_width(int width)
{
	m_size.set_width(width);
};

void sdlk::Box::set_height(int height)
{
	m_size.set_height(height);
};

sdlk::Box::Box(Size size) : m_size(size)
{
}

sdlk::Box::Box(Size size, Position position) : m_size(size), m_position(position)
{
}

sdlk::Box::Box(int width, int height, int x, int y)
	: m_size(Size(width, height)),
	  m_position(Position(x, y)) {};

bool sdlk::Box::operator==(const Box& other) const
{
	return this->m_size == other.m_size && this->m_position == other.m_position;
}
