#version 450

in vec2 textureCoords;

out vec4 out_Color;

uniform sampler2D guiTexture;
uniform vec4 guiColor;
uniform bool TextureMode = false;
uniform float HighlightIntensity = 1.0;

void main()
{	
	if(TextureMode)
		out_Color = texture(guiTexture,textureCoords) * HighlightIntensity;	
	else
		out_Color = guiColor;
}