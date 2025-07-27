#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 OutColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform bool uUseTextRendering;

void main()
{
    if (uUseTexture)
    {
        if (uUseTextRendering) {
            vec4 sampled = vec4(1.0, 1.0, 1.0, texture(uTexture, TexCoord).r);
            FragColor = OutColor * sampled;
        } else {
            FragColor = texture(uTexture, TexCoord);
        }
    } else {
        FragColor = OutColor;
    }
}
