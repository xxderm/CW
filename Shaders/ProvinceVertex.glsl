#version 450 compatibility
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;


out vec2 TexCoord;

void main(void){    
	vec2 texcoord = position.xz;
    TexCoord = texcoord;
	gl_Position = vec4(position, 1.0);
	
}