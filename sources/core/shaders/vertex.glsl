#version 330 core
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec4 aColor;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;
uniform vec4 uColor;

uniform bool uUseTexture;
uniform bool uUseVecColor;

out vec2 TexCoord;
out vec4 OutColor;

void main()
{
    gl_Position = uProjection * uView * uModel * vec4(aPos, 0.0, 1.0);
    TexCoord = uUseTexture ? aTexCoord : vec2(1.0);
    OutColor = uUseVecColor ? aColor : uColor;
}
