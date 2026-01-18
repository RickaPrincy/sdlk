#version 330 core

in vec4 out_color;
in vec2 text_coord;

out vec4 frag_color;

uniform bool u_use_texture;
uniform bool u_use_vertex_color;
uniform sampler2D u_texture;

void main()
{
    if(u_use_texture){
        frag_color = texture(u_texture, text_coord);
    } else {
        frag_color = out_color;
    }
}