#include <sdlk/core/properties/position.hpp>

sdlk::Position::Position(int x, int y) : m_x(x), m_y(y) {}
sdlk::Position::Position(int xy) : m_x(xy), m_y(xy) {}
