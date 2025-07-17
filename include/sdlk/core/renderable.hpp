#pragma once

#include <glad/glad.h>

#include <glm/vec2.hpp>
#include <sdlk/core/transformation.hpp>

namespace sdlk
{
	class renderable
	{
	protected:
		transformation m_transformation{};

	public:
		virtual auto render(GLuint *program) -> void;
		virtual auto bind() -> void const;

		virtual auto translate(glm::vec2 pixel_offset) -> void;

		virtual auto scale(glm::vec2 pixel_scale) -> void;

		virtual auto rotate(float angle_radians) -> void;

		virtual auto set_transformation_model(glm::mat4 transformation_model) -> void;

		virtual ~renderable() = default;
	};
}  // namespace sdlk
