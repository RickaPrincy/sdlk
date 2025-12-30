//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>

namespace sdlk
{
	class gl_program;

	class gl_uniform
	{
		gl_program *m_program{};

	public:
		explicit gl_uniform(gl_program *program);

		[[nodiscard]] auto get_loc(const std::string &name) const -> GLint;

		// ---- scalar ----
		auto set(const std::string &name, int value) const -> void;
		auto set(const std::string &name, float value) const -> void;
		auto set(const std::string &name, bool value) const -> void;

		// ---- vectors ----
		auto set(const std::string &name, const glm::vec2 &v) const -> void;
		auto set(const std::string &name, const glm::vec3 &v) const -> void;
		auto set(const std::string &name, const glm::vec4 &v) const -> void;

		// ---- matrices ----
		auto set(const std::string &name, const glm::mat3 &m) const -> void;
		auto set(const std::string &name, const glm::mat4 &m) const -> void;

		[[nodiscard]] static auto from(gl_program *program) -> std::shared_ptr<gl_uniform>;

		virtual ~gl_uniform() = default;
	};
}  // namespace sdlk
