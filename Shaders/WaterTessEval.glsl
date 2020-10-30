#version 450 core

layout(quads,fractional_odd_spacing,ccw)in;

out vec2 TexCoord;
out vec3 vertexPos;
out float depth;
out float h;

out vec2 fpos;

uniform sampler2D wterrain;
uniform mat4 mvp;
uniform float time;

uniform float speed;
uniform float amount;
uniform float height;
uniform vec3 cameraPos;
uniform sampler2D watnorm;
uniform mat4 model;


out mat3 TBN;
out vec3 normal;
out vec3 lightDir;
out vec3 viewDir;
out vec3 TangentLightPos;
out vec3 TangentViewPos;
out vec3 TangentFragPos;

in vec2 TexCoordTC[];
out vec2 TexCoordTE;

void main(){
    float u=gl_TessCoord.x;
    float v=gl_TessCoord.y;
    
    vec2 mapCoord=
    ((1-u)*(1-v)*TexCoordTC[0]+
    u*(1-v)*TexCoordTC[1]+
    u*v*TexCoordTC[2]+
    (1-u)*v*TexCoordTC[3]);
    TexCoordTE=mapCoord;
    
    vec4 a=mix(gl_in[1].gl_Position,gl_in[0].gl_Position,u);
    vec4 b=mix(gl_in[2].gl_Position,gl_in[3].gl_Position,u);
    vec4 position=mix(a,b,v);
    vertexPos=position.xyz;
    TexCoord=position.xz;
    float MAP_SIZE_X=128;
    float MAP_SIZE_Y=50;
    vec2 mapPos=position.xz;
    float heightScale=1.f;
    vec2 heightMapUV=vec2((mapPos.x)/MAP_SIZE_X,(mapPos.y)/MAP_SIZE_Y);
    //vec2((mapPos.x + 0.5f) / MAP_SIZE_X, (mapPos.y + 0.5f) / MAP_SIZE_Y);
    float y=0;
    if(cameraPos.y<3)
    y=sin(time*speed+(position.x*position.z*amount)+.5*cos(position.x*position.z*amount))*height;
    float hr=texture(wterrain,heightMapUV).r;
    // 0.365
    
    gl_Position=mvp*vec4(TexCoord.x,.3725490196078431+y,TexCoord.y,1.);
    depth=gl_Position.z;
    h=hr;
    fpos=heightMapUV;
    
    vec3 edge1=gl_in[2].gl_Position.xyz-gl_in[1].gl_Position.xyz;
    vec3 edge2=gl_in[3].gl_Position.xyz-gl_in[1].gl_Position.xyz;
    vec2 deltaUV1=TexCoordTC[2]-TexCoordTC[1];
    vec2 deltaUV2=TexCoordTC[3]-TexCoordTC[1];
    float f=1./(deltaUV1.x*deltaUV2.y-deltaUV2.x*deltaUV1.y);
    vec3 tangent1;
    vec3 bitangent1;
    tangent1.x=f*(deltaUV2.y*edge1.x-deltaUV1.y*edge2.x);
    tangent1.y=f*(deltaUV2.y*edge1.y-deltaUV1.y*edge2.y);
    tangent1.z=f*(deltaUV2.y*edge1.z-deltaUV1.y*edge2.z);
    tangent1=normalize(tangent1);
    bitangent1.x=f*(-deltaUV2.x*edge1.x+deltaUV1.x*edge2.x);
    bitangent1.y=f*(-deltaUV2.x*edge1.y+deltaUV1.x*edge2.y);
    bitangent1.z=f*(-deltaUV2.x*edge1.z+deltaUV1.x*edge2.z);
    bitangent1=normalize(bitangent1);
    
    vec3 T=normalize(vec3(model*vec4(tangent1,0.)));
    vec3 B=normalize(vec3(model*vec4(bitangent1,0.)));
    vec3 N=normalize(vec3(model*vec4(texture2D(watnorm,heightMapUV ).rgb,0.)));
    TBN=mat3(T,B,N);
    TBN=transpose(TBN);
    normal=texture2D(watnorm,heightMapUV).rgb;
    normal=normalize(normal*2.-1.);
    normal=normalize(TBN*normal);
    vec3 lightPos=vec3(MAP_SIZE_X+MAP_SIZE_X*10,5,MAP_SIZE_Y);
    vec3 viewPos=cameraPos;
    lightDir=TBN*normalize(lightPos-gl_Position.xyz);
    viewDir=TBN*normalize(viewPos-gl_Position.xyz);
    TangentLightPos=TBN*lightPos;
    TangentViewPos=TBN*viewPos;
    TangentFragPos=TBN*vec3(model*vec4(gl_Position.xyz,0.));
}