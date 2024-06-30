#pragma once

namespace sdlk
{
	class Position
	{
	public:
		int m_x = 0, m_y = 0;
		Position() = default;
		Position(int x, int y);
		Position(int xy);
	};
}  // namespace sdlk
