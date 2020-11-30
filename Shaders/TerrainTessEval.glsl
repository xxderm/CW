#version 450 core

layout(quads, fractional_odd_spacing, ccw) in;

out vec2 texcoord;
out float depth;
out float h;
out vec2 fpos;
out vec4 vpos;

out mat3 TBN;
out vec3 normal;
out vec3 lightDir;
out vec3 viewDir;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;
uniform vec3 campos;

uniform sampler2D terrain;
uniform mat4 mvp;

in vec2 TexCoordTC[];
out vec2 TexCoordTE;


uniform sampler2D terrain_map;
uniform sampler2D Rivers;
uniform sampler2D wn;
uniform mat4 model;

out vec3 fragmentPos;




out vec2 uv;
out vec2 uv2;


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
    vpos = position;

    float MAP_SIZE_X = 128;
    float MAP_SIZE_Y = 50;
    vec2 mapPos = position.xz;
    float heightScale = 1.f;
    vec2 heightMapUV = vec2((mapPos.x ) / MAP_SIZE_X, (mapPos.y ) / MAP_SIZE_Y);
    
    
  
    fpos = heightMapUV;

    float height = texture(terrain, heightMapUV).x * heightScale;

    gl_Position = mvp * vec4(texcoord.x, height + position.y, texcoord.y, 1.0);  
    depth = gl_Position.z;
    h = height;
    fragmentPos = position.xyz;

    //uv = vec2(position.x / MAP_SIZE_X, position.z / MAP_SIZE_Y);
    uv = vec2(u,v);
    uv2.x = position.x / MAP_SIZE_X;
    uv2.y = (position.z - MAP_SIZE_Y) / -MAP_SIZE_Y;    
    

    vec3 edge1 = gl_in[2].gl_Position.xyz - gl_in[1].gl_Position.xyz;
    vec3 edge2 = gl_in[3].gl_Position.xyz - gl_in[1].gl_Position.xyz;
    vec2 deltaUV1 = TexCoordTC[2] - TexCoordTC[1];
    vec2 deltaUV2 = TexCoordTC[3] - TexCoordTC[1];
    float f = 1.0 / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
    vec3 tangent1;
    vec3 bitangent1;
    tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
    tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
    tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
    tangent1 = normalize(tangent1);
    bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
    bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
    bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
    bitangent1 = normalize(bitangent1); 


    vec4 worldNormal = texture(wn, heightMapUV);


    vec3 T = normalize(vec3(model * vec4(tangent1,   0.0)));
    vec3 B = normalize(vec3(model * vec4(bitangent1, 0.0)));
    vec3 N = normalize(vec3(model * vec4(worldNormal.rgb,    0.0)));
    TBN = mat3(T, B, N);
    TBN = transpose(TBN);
    normal = worldNormal.rgb;
    normal = normalize(normal * 2.0 - 1.0);
    normal = normalize(TBN * normal);
    vec3 lightPos = vec3(MAP_SIZE_X + MAP_SIZE_X * 10, 15, MAP_SIZE_Y);
    vec3 viewPos = campos;
    lightDir = TBN * normalize(lightPos - position.xyz);
    viewDir  = TBN * normalize(viewPos - position.xyz); 
    TangentLightPos = TBN * lightPos;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * vec3(model * vec4(position.xyz, 0.0)); 
}