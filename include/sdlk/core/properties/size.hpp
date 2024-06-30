#pragma once

namespace sdlk
{
	class Size
	{
	public:
		int m_width = 10, m_height = 10;
		Size() = default;
		Size(int w, int h);
		Size(int wh);
	};
}  // namespace sdlk
