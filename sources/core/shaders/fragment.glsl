#version 330 core

in vec4 out_color;
in vec2 text_coord;

out vec4 frag_color;

uniform bool u_text_rendering;
uniform bool u_use_texture;
uniform bool u_use_vertex_color;
uniform sampler2D u_texture;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

vec4 msdf() {
    vec3 msd = texture(u_texture, text_coord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = 2.0 * (sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    return mix(vec4(0.0), out_color, opacity);
}

void main()
{
    if (u_text_rendering){
        frag_color = msdf();
    } else if (u_use_texture){
        frag_color = texture(u_texture, text_coord);
    } else {
        frag_color = out_color;
    }
}