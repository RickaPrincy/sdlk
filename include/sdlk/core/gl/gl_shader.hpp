//
// Created by ricka on 2025-12-30.
//

#pragma once

#include <glad/glad.h>

#include <memory>
#include <string>

namespace sdlk
{
	class gl_shader
	{
	protected:
		GLuint m_id{};
	public:
		explicit gl_shader(GLenum type, const std::string& source);

		[[nodiscard]] auto get_id() const -> GLuint;

		virtual ~gl_shader();

		[[nodiscard]] static auto from_file(GLenum type, const std::string &file_path) -> std::shared_ptr<gl_shader>;
	};

}  // namespace sdlk
