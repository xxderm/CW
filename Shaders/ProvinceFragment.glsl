#version 450 core
out vec4 fColor;
in vec2 fpos;

uniform sampler2D prov;
uniform sampler2D Countries;


uniform int currentDraw = 0; // 0 - Draw provinces
							 // 1 - Draw countries
						 
void main()
{	
	fColor = texture(prov, fpos);	
	if(currentDraw == 1)
		fColor = texture(Countries, fpos);	
}