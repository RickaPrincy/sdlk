#pragma once

#include <glad/glad.h>

#include <sdlk/core/transformation.hpp>

namespace sdlk
{
	class renderable
	{
	public:
		virtual auto render(GLuint *program) -> void = 0;

		virtual ~renderable() = default;
	};
}  // namespace sdlk
