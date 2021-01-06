#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec4 textColor;

const float width = 0.5;
const float edge = 0.1;


void main()
{
	//float distance = 1.0 - texture(text, TexCoords).r;
	//float alpha = 1.0 - smoothstep(width - edge, width + edge, distance);
	
	
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(text, TexCoords).r);
    color = vec4(textColor) * sampled;
}