//
// Created by ricka on 2025-12-30.
//

#include <sdlk/core/gl_program.hpp>
#include <stdexcept>

namespace sdlk
{
	gl_program::gl_program(const std::shared_ptr<gl_shader> &vertex_shader,
		const std::shared_ptr<gl_shader> &fragment_shader)
	{
		this->m_id = glCreateProgram();
		this->m_uniform = gl_uniform::from(this);

		glAttachShader(this->m_id, vertex_shader->get_id());
		glAttachShader(this->m_id, fragment_shader->get_id());
		glLinkProgram(this->m_id);

		GLint success{};
		glGetProgramiv(this->m_id, GL_LINK_STATUS, &success);
		if (!success)
		{
			char info_log[512];
			glGetProgramInfoLog(this->m_id, 512, nullptr, info_log);
			throw std::runtime_error(std::string("Program linking failed: ") + info_log);
		}
	}

	auto gl_program::get_id() const -> GLuint
	{
		return this->m_id;
	}

	auto gl_program::use() -> void
	{
		glUseProgram(this->m_id);
	}

	auto gl_program::get_uniform() const -> std::shared_ptr<gl_uniform>
	{
		return this->m_uniform;
	}

	auto gl_program::from_files(const std::string &vertex_path, const std::string &fragment_path)
		-> std::shared_ptr<gl_program>
	{
		return std::make_shared<gl_program>(gl_shader::from_file(GL_VERTEX_SHADER, vertex_path),
			gl_shader::from_file(GL_FRAGMENT_SHADER, fragment_path));
	}

	gl_program::~gl_program()
	{
		glDeleteProgram(this->m_id);
	}
}  // namespace sdlk
