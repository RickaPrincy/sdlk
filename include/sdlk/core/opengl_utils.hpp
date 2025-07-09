#pragma once

#include <glad/glad.h>

#include <string>

namespace sdlk
{
	[[nodiscard]] auto compile_shader(GLenum type, std::string source) -> GLuint;
	[[nodiscard]] auto create_shader_program(std::string vertex_source, std::string fragment_source)
		-> GLuint;
};	// namespace sdlk
