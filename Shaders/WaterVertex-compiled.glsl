#version 330 core
#define GLSLIFY 1
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 vertexPos;

uniform mat4 mvp;
uniform float time;

uniform float speed;
uniform float amount;
uniform float height;
uniform sampler2DRect terrain;
//out float h;

void main()
{
	vertexPos = aPos;
    
    float xx = (aPos.x-3) * (aPos.x-3);
    float yy = (aPos.y+1) * (aPos.y+1);

    gl_Position = vec4(aPos.x, 0, aPos.z, 1.0f);

    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}