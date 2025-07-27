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
		virtual auto scale(float scale) -> void;
		virtual auto rotate(float angle_radians) -> void;
		virtual auto add_translate(glm::vec2 pixel_offset) -> void;
		virtual auto add_scale(float scale) -> void;
		virtual auto add_rotation(float angle_radians) -> void;
		virtual auto set_transformation_model(glm::mat4 transformation_model) -> void;

		[[nodiscard]] virtual auto get_scale() -> float;
		[[nodiscard]] virtual auto get_rotation() -> float;
		[[nodiscard]] virtual auto get_translation() -> glm::vec2;

		renderable() = default;
		virtual ~renderable() = default;
	};
}  // namespace sdlk
