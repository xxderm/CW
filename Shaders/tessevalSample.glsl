#version 450 core

layout(quads, fractional_odd_spacing, ccw) in;

out vec2 texcoord;
in vec2 TexCoordTC[];
out vec2 TexCoordTE;

uniform mat4 mvp;


void main(){
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
    vec2 mapCoord =
	((1 - u) * (1 - v) * TexCoordTC[0] +
	u * (1 - v) * TexCoordTC[1] +
	u * v * TexCoordTC[2] +
	(1 - u) * v * TexCoordTC[3]);
    TexCoordTE = mapCoord;
    vec4 a = mix(gl_in[1].gl_Position, gl_in[0].gl_Position, u);
    vec4 b = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, u);
    vec4 position = mix(a, b, v);
    texcoord = position.xz;
    gl_Position = mvp * vec4(texcoord.x, position.y, texcoord.y, 1.0);  
}