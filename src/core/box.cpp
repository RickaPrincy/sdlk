#include <sdlk/core/box.hpp>

int sdlk::Box::get_x() const { return m_position.m_x; };
int sdlk::Box::get_y() const { return m_position.m_y; };
int sdlk::Box::get_width() const { return m_size.m_width; };
int sdlk::Box::get_height() const { return m_size.m_height; };

void sdlk::Box::set_x(int x) { m_position.m_x = x; };
void sdlk::Box::set_y(int y) { m_position.m_y = y; };
void sdlk::Box::set_width(int width) { m_size.m_width = width; };
void sdlk::Box::set_height(int height) { m_size.m_height = height; };

sdlk::Box::Box(Size size) : m_size(size) {}
sdlk::Box::Box(Size size, Position position)
    : m_size(size), m_position(position) {}
sdlk::Box::Box(int width, int height, int x, int y) {
  m_size = Size(width, height);
  m_position = Position(width, height);
};
