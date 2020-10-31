#version 450 core

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
uniform sampler2D bm3;

uniform sampler2D province_border;

uniform vec3 hoverEffect;

in float depth;

uniform int currentDraw=2;// 0 - Draw countries (politic map)
// 1 - Draw provinces
// 2 - Draw terrain

in vec2 fpos;
in vec3 fragmentPos;

vec4 terrain_map_texture;

in vec2 uv;
in vec2 uv2;

uniform vec3 campos;
uniform vec3 terpoint;
uniform float Tick;

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
	
	terrain_map_texture=texture(terrain_map,fpos);
	vec4 grasstexture=texture2D(TerrainTextureID,atlasTex(1));
	vec3 grassnormal=texture2D(an,atlasTex(1)).rgb;
	vec4 fieldstexture=texture2D(TerrainTextureID,atlasTex(0));
	vec3 fieldsnormal=texture2D(an,atlasTex(0)).rgb;
	//vec4 countrytexture=texture2D(TerrainTextureID,atlasTex(10));
	//vec3 countrynormal=texture2D(an,atlasTex(10)).rgb;
	vec4 lakestexture=texture2D(TerrainTextureID,atlasTex(6));
	vec3 lakesnormal=texture2D(an,atlasTex(6)).rgb;
	vec4 for1texture=texture2D(TerrainTextureID,atlasTex(4));
	vec3 for1normal=texture2D(an,atlasTex(4)).rgb;
	vec4 for2texture=texture2D(TerrainTextureID,atlasTex(5));
	vec3 for2normal=texture2D(an,atlasTex(5)).rgb;
	//vec4 moun3texture=texture2D(TerrainTextureID,atlasTex(7));
	//vec3 moun3normal=texture2D(an,atlasTex(7)).rgb;
	vec4 sandtexture=texture2D(TerrainTextureID,atlasTex(12));
	vec3 sandnormal=texture2D(an,atlasTex(12)).rgb;
	vec4 mounsandtexture=texture2D(TerrainTextureID,atlasTex(9));
	vec3 mounsandnormal=texture2D(an,atlasTex(9)).rgb;
	vec4 moun5texture=texture2D(TerrainTextureID,atlasTex(11));
	vec3 moun5normal=texture2D(an,atlasTex(11)).rgb;
	//vec4 moun1texture=texture2D(TerrainTextureID,atlasTex(2));
	//vec3 moun1normal=texture2D(an,atlasTex(2)).rgb;
	vec4 moun2texture=texture2D(TerrainTextureID,atlasTex(3));
	vec3 moun2normal=texture2D(an,atlasTex(3)).rgb;
	//vec4 moun4texture=texture2D(TerrainTextureID,atlasTex(8));
	//vec3 moun4normal=texture2D(an,atlasTex(8)).rgb;
	//vec4 moun6texture=texture2D(TerrainTextureID,atlasTex(15));
	//vec3 moun6normal=texture2D(an,atlasTex(15)).rgb;
	vec4 mounsand1texture=texture2D(TerrainTextureID,atlasTex(13));
	vec3 mounsand1normal=texture2D(an,atlasTex(13)).rgb;
	//vec4 mounsand2texture=texture2D(TerrainTextureID,atlasTex(14));
	//vec3 mounsand2normal=texture2D(an,atlasTex(14)).rgb;
	
	vec4 terratexture=texture(terra,fpos).rgba;
	vec4 bm = texture(bm3, fpos).rgba;
	
	vec4 currentTexture;

	vec3 currentNormal= grassnormal;	
	vec4 FinalColor = grasstexture;


	if(terrain_map_texture.rgb != vec3(0, 0, 0))
	{
		FinalColor = mix(FinalColor, lakestexture, terrain_map_texture.r);
		currentNormal = mix(currentNormal, lakesnormal, terrain_map_texture.r).rgb;

		FinalColor = mix(FinalColor, fieldstexture, terrain_map_texture.g);
		currentNormal = mix(currentNormal, fieldsnormal, terrain_map_texture.g).rgb;

		FinalColor = mix(FinalColor, for1texture, terrain_map_texture.b);
		currentNormal = mix(currentNormal, for1normal, terrain_map_texture.b).rgb;
	}
	if(terratexture.rgb != vec3(0, 0, 0))
	{
		FinalColor = mix(FinalColor, moun5texture, terratexture.r);
		currentNormal = mix(currentNormal, moun5normal, terratexture.r).rgb;

		FinalColor = mix(FinalColor, sandtexture, terratexture.g);
		currentNormal = mix(currentNormal, sandnormal, terratexture.g).rgb;

		FinalColor = mix(FinalColor, mounsandtexture, terratexture.b);
		currentNormal = mix(currentNormal, mounsandnormal, terratexture.b).rgb;
	}
	if(bm.rgb != vec3(0, 0, 0))
	{
		FinalColor = mix(FinalColor, mounsand1texture, bm.r);
		currentNormal = mix(currentNormal, mounsand1normal, bm.r).rgb;

		FinalColor = mix(FinalColor, moun2texture, bm.g);
		currentNormal = mix(currentNormal, moun2normal, bm.g).rgb;

		FinalColor = mix(FinalColor, for2texture, bm.b);
		currentNormal = mix(currentNormal, for2normal, bm.b).rgb;
	}

		

	fColor = FinalColor;
	

	if(currentDraw==1)
	{
		fColor=mix(currentTexture,provincemap,.4);
	}
	else if(currentDraw==0)
	{
		if(
			C3FB(countriesmap).r == 0 &&
			C3FB(countriesmap).g == 0 &&
			C3FB(countriesmap).b == 0
		)
		{
			fColor=vec4(0.0, 0.0, 0.0, 0.5);
		}
		else
			fColor=mix(countriesmap,currentTexture,0.1);
	}
	
	currentNormal=normalize(currentNormal*2.-1.);
	//currentNormal=normalize(TBN*currentNormal);
	
	vec3 color=fColor.rgb;
	vec3 ambient=.041*color;
	float diff=max(dot(lightDir,normal+currentNormal),0.);
	vec3 diffuse=diff*color;
	vec3 halfwayDir=normalize(lightDir);
	float spec=(max(dot(normal+currentNormal,halfwayDir),0.));
	vec3 specular=vec3(.122)*spec;
	
	fColor=vec4(ambient+diffuse+specular,1);

	if(hoverEffect.x == C3FB(provincemap).x && hoverEffect.y == C3FB(provincemap).y && hoverEffect.z == C3FB(provincemap).z)
		fColor.rgb *= (1 + abs(sin(Tick)));

}