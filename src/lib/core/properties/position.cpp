#include <sdlk/core/properties/position.hpp>

sdlk::Position::Position(int x, int y) : m_x(x), m_y(y)
{
}

sdlk::Position::Position(int xy) : m_x(xy), m_y(xy)
{
}

bool sdlk::Position::operator==(const sdlk::Position &other) const
{
	return other.m_x == this->m_x && other.m_y == this->m_y;
}
