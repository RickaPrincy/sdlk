#include "static_resource.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace sdlk
{
	static std::string load_file(const std::string& path)
	{
		std::ifstream file(path);
		if (!file)
		{
			throw std::runtime_error("Cannot open shader file: " + path);
		}

		std::ostringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}

	std::string resource::s_vertex_source = load_file("./resources/shaders/vertex.glsl");
	std::string resource::s_fragment_source = load_file("./resources/shaders/fragment.glsl");
}  // namespace sdlk
