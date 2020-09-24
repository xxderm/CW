#version 450 core

layout(quads, fractional_odd_spacing, ccw) in;

uniform mat4 mvp;
uniform sampler2D terrain;
in vec2 TexCoordTC[];
out vec2 fpos;
out vec2 texcoord;

void main(){
    float u = gl_TessCoord.x;
    float v = gl_TessCoord.y;
	
	
	vec2 mapCoord =
	((1 - u) * (1 - v) * TexCoordTC[0] +
	u * (1 - v) * TexCoordTC[1] +
	u * v * TexCoordTC[2] +
	(1 - u) * v * TexCoordTC[3]);
	

    vec4 a = mix(gl_in[1].gl_Position, gl_in[0].gl_Position, u);
    vec4 b = mix(gl_in[2].gl_Position, gl_in[3].gl_Position, u);
    vec4 position = mix(a, b, v);
	texcoord = position.xz;
	
	float MAP_SIZE_X = 128;
    float MAP_SIZE_Y = 50;
    vec2 mapPos = position.xz;
    float heightScale = 1.f;
    vec2 heightMapUV = vec2((mapPos.x ) / MAP_SIZE_X, (mapPos.y ) / MAP_SIZE_Y);
   
	float h = texture(terrain, heightMapUV).x * heightScale;
	
	fpos = heightMapUV;

    gl_Position = mvp * vec4(texcoord.x, h + position.y, texcoord.y, 1.0);  
 
}