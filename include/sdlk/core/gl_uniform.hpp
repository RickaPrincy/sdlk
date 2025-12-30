//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <glad/glad.h>

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

		[[nodiscard]] static auto from(gl_program *program) -> std::shared_ptr<gl_uniform>;

		virtual ~gl_uniform() = default;
	};
}  // namespace sdlk
