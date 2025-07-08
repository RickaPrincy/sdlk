#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <sdlk/core/types.hpp>

namespace sdlk
{
	class shape
	{
	private:
		polygon m_polygon{};
		int m_indices_count{};

	protected:
		GLuint m_vao{}, m_vbo{}, m_ebo{};

	public:
		shape(sdlk::polygon polygon, const int &window_width, const int &window_height);

		auto draw() -> void const;

		~shape();
	};
}  // namespace sdlk
