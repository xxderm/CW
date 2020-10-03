#version 450 compatibility
out vec4 fColor;

in vec2 TexCoordTE;
in float h;

in mat3 TBN;
in vec3 normal;
in vec3 lightDir;
in vec3 viewDir;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;

in vec3 terrain_color;
in vec3 river_color;

#define numberOfRows 4
#define atlasTex(index)(uv.xy/numberOfRows)+vec2(float(index%numberOfRows)/float(numberOfRows),float(index/numberOfRows)/float(numberOfRows))

uniform sampler2D provinces;
uniform sampler2D states;
uniform sampler2D terrain_map;
uniform sampler2D terra;

uniform sampler2D TerrainTextureID;
uniform sampler2D an;
uniform sampler2D fbotest;

uniform sampler2D Countries;
uniform sampler2D countryborder;

uniform sampler2D province_border;

in float depth;

uniform int currentDraw=0;// 0 - Draw countries (politic map)
// 1 - Draw provinces
// 2 - Draw terrain

in vec2 fpos;
in vec3 fragmentPos;

vec4 terrain_map_texture;

in vec2 uv;
in vec2 uv2;

uniform vec3 campos;
uniform vec3 terpoint;

#define F2B(f)((f)>=1.?255:int(((f)*255.)))
#define V3FB vec3(F2B(terrain_map_texture.r),F2B(terrain_map_texture.g),F2B(terrain_map_texture.b))
#define C3FB(tx)vec3(F2B(tx.r),F2B(tx.g),F2B(tx.b))

vec3 RGBtoHSV(vec3 RGB )
{
	float Cmax = max( RGB.r, max( RGB.g, RGB.b ) );
	float Cmin = min( RGB.r, min( RGB.g, RGB.b ) );
	float diff = Cmax - Cmin;
	
	float H = 0.0;
	float S = 0.0;
	if (diff != 0.0)
	{
		S = diff / Cmax;
		
		if (Cmax == RGB.r)
			H = (RGB.g - RGB.b) / diff + 6.0;
		else if (Cmax == RGB.g)
			H = (RGB.b - RGB.r) / diff + 2.0;
		else
			H = (RGB.r - RGB.g) / diff + 4.0;
	}

	return vec3(H, S, Cmax);
}

float defWeight(vec3 c,vec4 tt)
{	
	// vec3 ttb = C3FB(tt).rgb;
	// vec3 tmb = C3FB(terrain_map_texture).rgb;
	// if(ttb.r > c.r || ttb.g > c.g || ttb.b > c.b)
	// 	return 0;
	// float r1 = ((ttb.r / c.r) + (ttb.g / c.g) + (ttb.b / c.b)) ;
	// return r1 /.;	
	return 0;
}

float remap(vec3 vminval, vec3 vmaxval, vec3 vcurval)
{
	vec4 res = vec4((vcurval - vminval) / (vmaxval - vminval), 1.);
	//return res;


	float r = smoothstep(vminval.r, vmaxval.r, vcurval.r);
	float g = smoothstep(vminval.g, vmaxval.g, vcurval.g);
	float b = smoothstep(vminval.b, vmaxval.b, vcurval.b);	

	if(r > 1. || g > 1. || b > 1.)
		return 0.;

	float resf = (r + g + b) / 3.;
	

	return resf;
	//return (res.r + res.g + res.b) / 3.5;
}

void main()
{
	vec4 provincemap=texture(provinces,fpos);
	vec4 countriesmap=texture(Countries,fpos);
	vec4 countrybordertex=texture(countryborder,fpos);
	vec4 provbord=texture(province_border,fpos);
	
	terrain_map_texture=texture(terrain_map,fpos);
	vec4 grasstexture=texture2D(TerrainTextureID,atlasTex(1));
	vec3 grassnormal=texture2D(an,atlasTex(1)).rgb;
	vec4 fieldstexture=texture2D(TerrainTextureID,atlasTex(0));
	vec3 fieldsnormal=texture2D(an,atlasTex(0)).rgb;
	vec4 countrytexture=texture2D(TerrainTextureID,atlasTex(10));
	vec3 countrynormal=texture2D(an,atlasTex(10)).rgb;
	vec4 lakestexture=texture2D(TerrainTextureID,atlasTex(6));
	vec3 lakesnormal=texture2D(an,atlasTex(6)).rgb;
	vec4 for1texture=texture2D(TerrainTextureID,atlasTex(4));
	vec3 for1normal=texture2D(an,atlasTex(4)).rgb;
	vec4 for2texture=texture2D(TerrainTextureID,atlasTex(5));
	vec3 for2normal=texture2D(an,atlasTex(5)).rgb;
	vec4 moun3texture=texture2D(TerrainTextureID,atlasTex(7));
	vec3 moun3normal=texture2D(an,atlasTex(7)).rgb;
	vec4 sandtexture=texture2D(TerrainTextureID,atlasTex(12));
	vec3 sandnormal=texture2D(an,atlasTex(12)).rgb;
	vec4 mounsandtexture=texture2D(TerrainTextureID,atlasTex(9));
	vec3 mounsandnormal=texture2D(an,atlasTex(9)).rgb;
	vec4 moun5texture=texture2D(TerrainTextureID,atlasTex(11));
	vec3 moun5normal=texture2D(an,atlasTex(11)).rgb;
	vec4 moun1texture=texture2D(TerrainTextureID,atlasTex(2));
	vec3 moun1normal=texture2D(an,atlasTex(2)).rgb;
	vec4 moun2texture=texture2D(TerrainTextureID,atlasTex(3));
	vec3 moun2normal=texture2D(an,atlasTex(3)).rgb;
	vec4 moun4texture=texture2D(TerrainTextureID,atlasTex(8));
	vec3 moun4normal=texture2D(an,atlasTex(8)).rgb;
	vec4 moun6texture=texture2D(TerrainTextureID,atlasTex(15));
	vec3 moun6normal=texture2D(an,atlasTex(15)).rgb;
	vec4 mounsand1texture=texture2D(TerrainTextureID,atlasTex(13));
	vec3 mounsand1normal=texture2D(an,atlasTex(13)).rgb;
	vec4 mounsand2texture=texture2D(TerrainTextureID,atlasTex(14));
	vec3 mounsand2normal=texture2D(an,atlasTex(14)).rgb;
	
	vec4 terratexture=texture(terra,fpos).rgba;
	
	vec4 currentTexture;
	vec3 currentNormal=vec3(0,0,0);	

	vec4 FinalColor = vec4(0, 0, 0, 1);

	float modify= 0.;
	if(C3FB(terrain_map_texture) == vec3(75, 147, 174))
		modify = 0.86;

	float modify1 = 0.;
	if(C3FB(terratexture) == vec3(255, 0, 127))
		modify1 = 0.85;

	float modify2 = 0.;
	if(C3FB(terrain_map_texture) == vec3(86, 124, 27))
		modify2 = 0.35;

	float modify3 = 0.;
	if(C3FB(terrain_map_texture) == vec3(255, 0, 24))
		modify3 = 0.25;

	float modify4 = 0.;
	if(C3FB(terrain_map_texture) == vec3(0, 86, 6))
		modify4 = 0.35;
	
	
	FinalColor = mix(FinalColor, mounsand1texture, remap(vec3(200, 115, 144), vec3(174, 0, 255), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, mounsand2texture, remap(vec3(85, 74, 54), vec3(73, 59, 15), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun6texture, remap(vec3(165, 126, 97), vec3(243, 199, 147), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, for2texture, remap(vec3(94, 53, 50), vec3(255, 0, 127), C3FB(terratexture).rgb) + modify1 );
	FinalColor = mix(FinalColor, moun5texture, remap(vec3(127, 122, 115), vec3(255, 255, 255), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun3texture, remap(vec3(150, 117, 22), vec3(134, 84, 30), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun4texture, remap(vec3(206, 143, 109), vec3(255, 0, 240), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun3texture,  remap(vec3(79, 124, 38), vec3(58, 131, 82), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun5texture, remap(vec3(76, 103, 74), vec3(92, 83, 26), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, mounsandtexture, remap(vec3(244, 241, 14), vec3(206, 169, 99), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, sandtexture, remap(vec3(223, 189, 68), vec3(252, 255, 0), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, moun1texture, remap(vec3(86, 125, 26), vec3(132, 255, 0), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, grasstexture, (remap(vec3(8,31, 129), vec3(86, 124, 27), C3FB(terratexture).rgb) + modify2));
	FinalColor = mix(FinalColor, countrytexture, (remap(vec3(181, 205, 9), vec3(240, 255, 0), C3FB(terratexture).rgb)) );
	FinalColor = mix(FinalColor, for2texture, remap(vec3(85, 124, 27), vec3(6, 200, 11), C3FB(terratexture).rgb));
	FinalColor = mix(FinalColor, lakestexture, remap(vec3(86, 124, 28), vec3(75, 147, 174), C3FB(terratexture).rgb) + modify);
	FinalColor = mix(FinalColor, moun2texture, remap(vec3(112, 76, 24), vec3(112, 74, 31), C3FB(terratexture).rgb) );
	FinalColor = mix(FinalColor, for1texture,  remap(vec3(70, 109, 37), vec3(0, 86, 6), C3FB(terratexture).rgb) + modify4);
	FinalColor = mix(FinalColor, fieldstexture, remap(vec3(86, 123, 27), vec3(255, 0, 24), C3FB(terratexture).rgb) + modify3);

	
	currentNormal = mix(currentNormal, mounsand1normal, remap(vec3(200, 115, 144), vec3(174, 0, 255), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, mounsand2normal, remap(vec3(85, 74, 54), vec3(73, 59, 15), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun6normal, remap(vec3(165, 126, 97), vec3(243, 199, 147), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, for2normal, remap(vec3(94, 53, 50), vec3(255, 0, 127), C3FB(terratexture).rgb) + modify1 ).rgb;
	currentNormal = mix(currentNormal, moun5normal, remap(vec3(127, 122, 115), vec3(255, 255, 255), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun3normal, remap(vec3(150, 117, 22), vec3(134, 84, 30), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun5normal,  remap(vec3(76, 103, 74), vec3(92, 83, 26), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun4normal, remap(vec3(206, 143, 109), vec3(255, 0, 240), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun3normal, remap(vec3(79, 124, 38), vec3(58, 131, 82), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, mounsandnormal, remap(vec3(244, 241, 14), vec3(206, 169, 99), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, sandnormal, remap(vec3(223, 189, 68), vec3(252, 255, 0), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, moun1normal, remap(vec3(86, 125, 26), vec3(132, 255, 0), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, grassnormal, (remap(vec3(8,31, 129), vec3(86, 124, 27), C3FB(terratexture).rgb) + modify2));
	currentNormal = mix(currentNormal, countrynormal, (remap(vec3(181, 205, 9), vec3(240, 255, 0), C3FB(terratexture).rgb)) ).rgb;
	currentNormal = mix(currentNormal, for2normal, remap(vec3(85, 124, 27), vec3(6, 200, 11), C3FB(terratexture).rgb)).rgb;
	currentNormal = mix(currentNormal, lakesnormal, remap(vec3(86, 124, 28), vec3(75, 147, 174), C3FB(terratexture).rgb) + modify).rgb;	
    currentNormal = mix(currentNormal, moun2normal, remap(vec3(112, 76, 24), vec3(112, 74, 31), C3FB(terratexture).rgb) ).rgb;
	currentNormal = mix(currentNormal, for1normal, remap(vec3(70, 109, 37), vec3(0, 86, 6), C3FB(terratexture).rgb) + modify4).rgb;
	currentNormal = mix(currentNormal, fieldsnormal, remap(vec3(86, 123, 27), vec3(255, 0, 24), C3FB(terratexture).rgb) + modify3).rgb;
	

	
	// FinalColor = (
	// (grasstexture * defWeight(vec3(86,124,27), terratexture) ) +
	// (fieldstexture * defWeight(vec3(255,0,24), terratexture) ) +
	// (countrytexture * defWeight(vec3(240,255,0), terratexture) ) +
	// (lakestexture * defWeight(vec3(75,147,174), terratexture) ) +
	// (moun1texture * defWeight(vec3(132, 255,0), terratexture) ) +
	// (moun2texture * defWeight(vec3(112,74,31), terratexture) ) +
	// (moun3texture * defWeight(vec3(58,131,82), terratexture) ) +
	// (moun5texture * defWeight(vec3(92,83,76), terratexture) ) +
	// (for1texture * defWeight(vec3(0,86,6), terratexture) ) +
	// (for2texture * defWeight(vec3(6,200,11), terratexture) ) +
	// (sandtexture * defWeight(vec3(252,255,0), terratexture) ) +
	// (mounsandtexture * defWeight(vec3(206,169,99), terratexture) ) +
	// (mounsand1texture * defWeight(vec3(174,0,255), terratexture) ) +
	// (mounsand2texture * defWeight(vec3(73,59,15), terratexture) ) +
	// (moun4texture * defWeight(vec3(255,0,240), terratexture) ) +
	// (mounsand2texture * defWeight(vec3(243,199,147), terratexture) ) +

	// ((moun5texture * 8) * defWeight(vec3(255,255,255), terratexture) ) +
	// ((moun3texture) * defWeight(vec3(134,84,30), terratexture) ) +
	// ((for2texture) * defWeight(vec3(255,0,127), terratexture) ) 
	// );


	// currentNormal = (
	// (grassnormal * defWeight(vec3(86,124,27), terratexture) ) +
	// (fieldsnormal * defWeight(vec3(255,0,24), terratexture) ) +
	// (countrynormal * defWeight(vec3(240,255,0), terratexture) ) +
	// (lakesnormal * defWeight(vec3(75,147,174), terratexture) ) +
	// (moun1normal * defWeight(vec3(132, 255,0), terratexture) ) +
	// (moun2normal * defWeight(vec3(112,74,31), terratexture) ) +
	// (moun3normal * defWeight(vec3(58,131,82), terratexture) ) +
	// (moun5normal * defWeight(vec3(92,83,76), terratexture) ) +
	// (for1normal * defWeight(vec3(0,86,6), terratexture) ) +
	// (for2normal * defWeight(vec3(6,200,11), terratexture) ) +
	// (sandnormal * defWeight(vec3(252,255,0), terratexture) ) +
	// (mounsandnormal * defWeight(vec3(206,169,99), terratexture) ) +
	// (mounsand1normal * defWeight(vec3(174,0,255), terratexture) ) +
	// (mounsand2normal * defWeight(vec3(73,59,15), terratexture) ) +
	// (moun4normal * defWeight(vec3(255,0,240), terratexture) ) +
	// (mounsand2normal * defWeight(vec3(243,199,147), terratexture) ) +

	// ((moun5normal * 8) * defWeight(vec3(255,255,255), terratexture) ) +
	// (moun3normal * defWeight(vec3(134,84,30), terratexture) ) +
	// (for2normal * defWeight(vec3(255,0,127), terratexture) )
	// );
	

	fColor = FinalColor;
	

	if(currentDraw==1)
	{
		fColor=mix(currentTexture,provincemap,.6);
	}
	else if(currentDraw==0)
	{
		if(
			C3FB(countriesmap).r == 0 &&
			C3FB(countriesmap).g == 0 &&
			C3FB(countriesmap).b == 0
		)
		{
			fColor=countrybordertex;
		}
		else
			fColor=mix(countriesmap,currentTexture,1/campos.y);
	}
	
	currentNormal=normalize(currentNormal*2.-1.);
	currentNormal=normalize(TBN*currentNormal);
	
	vec3 color=fColor.rgb;
	vec3 ambient=.1*color;
	float diff=max(dot(lightDir,normal+currentNormal),0.);
	vec3 diffuse=diff*color;
	vec3 halfwayDir=normalize(lightDir);
	float spec=(max(dot(normal+currentNormal,halfwayDir),0.));
	vec3 specular=vec3(.2)*spec;// assuming bright white light color
	
	fColor=vec4(ambient+diffuse+specular,1);
	//fColor = terratexture;
}