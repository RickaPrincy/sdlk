#include "static_resource.hpp"

namespace sdlk
{
	std::string resource::s_vertex_source = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
}
)glsl";

	std::string resource::s_fragment_source = R"glsl(
#version 330 core
out vec4 FragColor;

void main()
{
    FragColor = vec4(0.4, 0.7, 0.9, 1.0);
}
)glsl";

}  // namespace sdlk
