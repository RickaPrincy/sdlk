//
// Created by ricka on 2025-12-30.
//

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
}  // namespace sdlk
