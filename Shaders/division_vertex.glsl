#version 450 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texCoord;

out vec2 TexCoord;
uniform mat4 mvp;

void main(void){
    vec2 texcoord = position.xz;
    TexCoord = texcoord;
    vec4 displaced = vec4(
        position.x, position.y,
        position.z, 1.0);
    gl_Position = displaced;
}