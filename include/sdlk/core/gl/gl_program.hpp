//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <memory>
#include <glad/glad.h>
#include <sdlk/core/gl/gl_shader.hpp>
#include <sdlk/core/gl/gl_uniform.hpp>

namespace sdlk
{
	class gl_program
	{
	protected:
		GLuint m_id{};
		std::shared_ptr<gl_uniform> m_uniform{};

	public:
		explicit gl_program(const std::shared_ptr<gl_shader> &vertex_shader,
			const std::shared_ptr<gl_shader> &fragment_shader);

		auto use() -> void;

		[[nodiscard]] auto get_id() const -> GLuint;
		[[nodiscard]] auto get_uniform() const -> std::shared_ptr<gl_uniform>;

		[[nodiscard]] static auto from_files(const std::string &vertex_path,
			const std::string &fragment_path) -> std::shared_ptr<gl_program>;

		virtual ~gl_program();
	};

}  // namespace sdlk