//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/gl_shader.hpp>
#include <stdexcept>
#include "../utils/file.hpp"

namespace sdlk
{
	gl_shader::gl_shader(const GLenum type, const std::string& source)
	{
		const auto source_ctr = source.c_str();
		this->m_id = glCreateShader(type);

		glShaderSource(this->m_id, 1, &source_ctr, nullptr);
		glCompileShader(this->m_id);

		GLint success{};
		glGetShaderiv(this->m_id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char info_log[512];
			glGetShaderInfoLog(this->m_id, 512, nullptr, info_log);
			throw std::runtime_error(std::string("Shader compilation failed: ") + info_log);
		}
	}

	auto gl_shader::get_id() const -> GLuint
	{
		return this->m_id;
	}

	auto gl_shader::from_file(const GLenum type, const std::string& file_path)
		-> std::shared_ptr<gl_shader>
	{
		return std::make_shared<gl_shader>(type,  file::read(file_path));
	}

	gl_shader::~gl_shader()
	{
		glDeleteShader(this->m_id);
	}
}  // namespace sdlk