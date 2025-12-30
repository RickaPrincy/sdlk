//
// Created by ricka on 2025-12-30.
//

#pragma once

namespace sdlk
{
	class renderable
	{
	public:
		renderable() = default;

		virtual auto render() -> void = 0;

		virtual ~renderable() = default;
	};
}