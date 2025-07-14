#include "static_resource.hpp"

namespace sdlk
{
	std::string resource::s_vertex_source = R"glsl(
#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform bool u_useTexture;

out vec2 TexCoord;
out vec4 OutColor;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 0.0, 1.0);
    
    if(u_useTexture){
        TexCoord = aTexCoord;
        OutColor = vec4(1.0);
    }else{
        TexCoord = vec2(1.0);
        OutColor = aColor;
    }
}
)glsl";

	std::string resource::s_fragment_source = R"glsl(
#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 OutColor;

uniform sampler2D u_texture;
uniform bool u_useTextRendering;
uniform bool u_useTexture;
uniform vec4 text_color;

void main()
{
    if(u_useTexture)
    {
        if(u_useTextRendering){
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, TexCoord).r);
            FragColor = text_color * sampled;
        }else{
            FragColor = texture(u_texture, TexCoord);
        }
    }else{
        FragColor = OutColor;
    }
}
)glsl";

}  // namespace sdlk
