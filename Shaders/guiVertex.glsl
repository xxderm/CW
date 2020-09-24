#version 450

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 textureCoords;

uniform mat4 transformationMatrix;
uniform mat4 mvp;

void main(void)
{
	gl_Position = transformationMatrix * vec4(position, 0.0, 1.0);
	textureCoords = vec2((position.x + 1.0) / 2.0, 1 - (position.y + 1.0) / 2.0);
}