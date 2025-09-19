#version 330 core
out vec4 FragColor;

in vec2 TexCoord;
in vec4 OutColor;

uniform sampler2D uTexture;
uniform bool uUseTexture;
uniform bool uUseTextRendering;
uniform bool uDebugTexture;   // <--- nouveau uniform toggle
uniform vec4 uBgColor;
uniform vec4 uFgColor;
uniform float uPxRange;

float median(float r, float g, float b) {
    return max(min(r, g), min(max(r, g), b));
}

float screenPxRange() {
    vec2 unitRange = vec2(uPxRange) / vec2(textureSize(uTexture, 0));
    vec2 screenTexSize = vec2(1.0) / fwidth(TexCoord);
    return max(0.5 * dot(unitRange, screenTexSize), 1.0);
}

vec4 renderText() {
    vec3 msd = texture(uTexture, TexCoord).rgb;
    float sd = median(msd.r, msd.g, msd.b);
    float screenPxDistance = screenPxRange()*(sd - 0.5);
    float opacity = clamp(screenPxDistance + 0.5, 0.0, 1.0);
    return mix(uBgColor, uFgColor, opacity);
}

// nouvelle fonction debug
vec4 renderTextureDebug() {
    return texture(uTexture, TexCoord);
}

void main()
{
    if (uUseTexture)
    {
        if (uDebugTexture) {
            FragColor = renderTextureDebug();   // 🔍 Debug direct
        }
        else if (uUseTextRendering) {
            FragColor = renderText();
        }
        else {
            FragColor = texture(uTexture, TexCoord);
        }
    }
    else {
        FragColor = OutColor;
    }
}