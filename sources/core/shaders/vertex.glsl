#version 330 core

layout (location = 0) in vec3 a_pos;
layout (location = 1) in vec4 a_color;
layout (location = 2) in vec2 a_uv;

uniform bool u_use_texture;
uniform bool u_use_vertex_color;
uniform vec4 u_color;

out vec4 out_color;
out vec2 text_coord;

void main()
{
    gl_Position = vec4(a_pos, 1.0);
    text_coord = u_use_texture ? a_uv : vec2(1.0);
    out_color = u_use_vertex_color ? a_color : u_color;
}