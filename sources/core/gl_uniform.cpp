//
// Created by ricka on 2025-12-30.
//

#include <glm/gtc/type_ptr.hpp>
#include <sdlk/core/gl_program.hpp>
#include <sdlk/core/gl_uniform.hpp>
#include <stdexcept>
#include <string>

namespace sdlk
{
	gl_uniform::gl_uniform(gl_program *program) : m_program(program)
	{}

	auto gl_uniform::get_loc(const std::string &name) const -> GLint
	{
		const auto loc = glGetUniformLocation(this->m_program->get_id(), name.c_str());

		if (loc == -1)
		{
			throw std::runtime_error("Cannot get the location of " + name);
		}

		return loc;
	}

	auto gl_uniform::from(gl_program *program) -> std::shared_ptr<gl_uniform>
	{
		return std::make_shared<gl_uniform>(program);
	}

	// ---- scalar ----
	auto gl_uniform::set(const std::string &name, const int value) const -> void
	{
		glUniform1i(get_loc(name), value);
	}

	auto gl_uniform::set(const std::string &name, const float value) const -> void
	{
		glUniform1f(get_loc(name), value);
	}

	auto gl_uniform::set(const std::string &name, const bool value) const -> void
	{
		set(name, static_cast<int>(value));
	}

	// ---- vectors ----
	auto gl_uniform::set(const std::string &name, const glm::vec2 &v) const -> void
	{
		glUniform2fv(get_loc(name), 1, glm::value_ptr(v));
	}

	auto gl_uniform::set(const std::string &name, const glm::vec3 &v) const -> void
	{
		glUniform3fv(get_loc(name), 1, glm::value_ptr(v));
	}

	auto gl_uniform::set(const std::string &name, const glm::vec4 &v) const -> void
	{
		glUniform4fv(get_loc(name), 1, glm::value_ptr(v));
	}

	// ---- matrices ----
	auto gl_uniform::set(const std::string &name, const glm::mat3 &m) const -> void
	{
		glUniformMatrix3fv(get_loc(name), 1, GL_FALSE, glm::value_ptr(m));
	}

	auto gl_uniform::set(const std::string &name, const glm::mat4 &m) const -> void
	{
		glUniformMatrix4fv(get_loc(name), 1, GL_FALSE, glm::value_ptr(m));
	}
}  // namespace sdlk
