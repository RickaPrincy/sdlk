#include <sdlk/core/opengl_utils.hpp>
#include <stdexcept>

namespace sdlk
{
	auto compile_shader(GLenum type, std::string source) -> GLuint
	{
		auto source_ctr = source.c_str();
		GLuint shader = glCreateShader(type);
		glShaderSource(shader, 1, &source_ctr, nullptr);
		glCompileShader(shader);

		GLint success{};
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Shader compilation failed: ") + infoLog);
		}
		return shader;
	}

	auto create_shader_program(std::string vertex_source, std::string fragment_source) -> GLuint
	{
		GLuint vertexShader = compile_shader(GL_VERTEX_SHADER, vertex_source.c_str());
		GLuint fragmentShader = compile_shader(GL_FRAGMENT_SHADER, fragment_source.c_str());

		GLuint program = glCreateProgram();
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);
		glLinkProgram(program);

		GLint success{};
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetProgramInfoLog(program, 512, nullptr, infoLog);
			throw std::runtime_error(std::string("Program linking failed: ") + infoLog);
		}

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		return program;
	}

	[[nodiscard]] auto get_uniform_loc(GLuint *program, std::string uniform_name) -> GLuint
	{
		auto loc = glGetUniformLocation(*program, uniform_name.c_str());

		if (loc == -1)
		{
			throw std::runtime_error("Cannot get the location of " + uniform_name);
		}

		return loc;
	}

}  // namespace sdlk
