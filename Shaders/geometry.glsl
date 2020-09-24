#version 400 compatibility

uniform mat4 mvp;

layout(triangles, invocations = 1) in;
layout(triangle_strip, max_vertices = 3) out;
in vec3 teNormal[];
out float gLightIntensity;

const vec3 LIGHTPOS = vec3( 0., 5., -1. );
const float uShrink = 1;
vec3 V[3];
vec3 CG;

in PipelineData {
    vec4 position;
    vec3 color;
} te_in[];

out PipelineData {
    vec4 position;
    vec3 color;
} te_out;

void ProduceVertex( int v )
{
    gLightIntensity = abs( dot( normalize(LIGHTPOS - V[v]), normalize(teNormal[v]) ) );
    te_out.position = mvp * vec4( CG + uShrink * ( V[v] - CG ), 1. );
    gl_Position = te_out.position;
    EmitVertex( );
}

void main( )
{
    te_out.color = te_in[gl_InvocationID].color;

    V[0] = te_in[0].position.xyz;
    V[1] = te_in[1].position.xyz;
    V[2] = te_in[2].position.xyz;
    CG = ( V[0] + V[1] + V[2] ) / 3.;
    ProduceVertex( 0 );
    ProduceVertex( 1 );
    ProduceVertex( 2 );
}
   