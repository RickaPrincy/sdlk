#include <sdlk/core/properties/size.hpp>

sdlk::Size::Size(int width, int height) : m_width(width), m_height(height)
{
}

sdlk::Size::Size(int width_heigth) : m_width(width_heigth), m_height(width_heigth)
{
}

bool sdlk::Size::operator==(const sdlk::Size &other) const
{
	return other.m_width == this->m_width && other.m_height == this->m_height;
}
