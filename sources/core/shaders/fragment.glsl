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
    if (u_useTexture)
    {
        if (u_useTextRendering) {
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, TexCoord).r);
            FragColor = text_color * sampled;
        } else {
            FragColor = texture(u_texture, TexCoord);
        }
    } else {
        FragColor = OutColor;
    }
}
