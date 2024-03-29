#version 330 core
#define GLSLIFY 1
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

void main()
{
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture2D(text, TexCoords).r);
    color = vec4(textColor) * sampled;
}