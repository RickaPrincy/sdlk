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

    if (u_useTexture) {
        TexCoord = aTexCoord;
        OutColor = vec4(1.0);
    } else {
        TexCoord = vec2(1.0);
        OutColor = aColor;
    }
}
