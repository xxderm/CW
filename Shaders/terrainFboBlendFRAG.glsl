#version 450 compatibility
out vec4 fColor;
uniform sampler2D fbotest;
void main()
{	
	ivec2 tsize = textureSize(fbotest, 0);
	vec2 screntc = gl_FragCoord.xy * (1.0 / vec2(tsize));
	fColor = texture(fbotest, screntc);
}