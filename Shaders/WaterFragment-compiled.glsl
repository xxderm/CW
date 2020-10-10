#version 330 core
#define GLSLIFY 1
out vec4 FragColor;

in vec3 vertexPos;
in vec2 TexCoord;
in float h;
in vec2 fpos;

uniform sampler2D TexWater;
uniform samplerCube skybox;
uniform sampler2D cm;
uniform vec3 cameraPos;
in mat3 TBN;
in vec3 normal;
in vec3 lightDir;
in vec3 viewDir;
in vec3 TangentLightPos;
in vec3 TangentViewPos;
in vec3 TangentFragPos;
uniform sampler2D dudv;
uniform float moveFactor;

void main()
{
    vec2 distortion1 = (texture(dudv, vec2(TexCoord.x + moveFactor, TexCoord.y)).rg * 2.0 - 1.0) * 0.12;
    vec2 distortion2 = (texture(dudv, vec2(-TexCoord.x + moveFactor, TexCoord.y + moveFactor)).rg * 2.0 - 1.0) * 0.12;
    vec2 distortion = distortion1 + distortion2;

    vec4 tmp = mix(texture(cm, fpos),texture(TexWater, TexCoord), 0.5);
    FragColor = vec4(tmp.rgb, 0.9f);

    vec3 Normals = normalize(cross(dFdx(vertexPos), dFdy(vertexPos))) ;

    float ratio = 1.00 / 1.33;
    vec3 I = normalize(vertexPos - cameraPos);
    vec3 refraction = refract(I, normalize(-Normals), ratio);
    refraction += vec3(distortion, ratio);
    refraction = clamp(refraction, 0.001, 0.999);

    FragColor *= vec4(texture(skybox, refraction).rgb, 1.0);

    vec3 reflection = reflect(I, normalize(-Normals));  
    reflection += vec3(distortion, ratio);
    reflection.x = clamp(reflection.x, 0.001, 0.999);
    reflection.z = clamp(reflection.z, -0.999, -0.001);

    FragColor *= vec4(texture(skybox, reflection).rgb, 1.0);

    vec3 diffuse = vec3(-1.0, -1.0, -1.0);
    float attenuation =  dot(-normalize(cross(dFdx(vertexPos), dFdy(vertexPos))), diffuse);
    attenuation = max(attenuation, 0.0);

    vec3 hazy_ambiant = 0.4 * vec3(0.741, 0.745, 0.752);
    vec3 sunrise_ambiant = 0.4 * vec3(0.713, 0.494, 0.356);

    FragColor.xyz *= (hazy_ambiant + attenuation);
    FragColor.a = 0 + (h / 0.5) ;	

    vec3 color=FragColor.rgb;
	vec3 ambient=1.9*color;
	float diff=max(dot(lightDir,normal),0.);
	vec3 diffuse2=diff*color;
	vec3 halfwayDir=normalize(lightDir);
	float spec=(max(dot(normal,halfwayDir),0.));
	vec3 specular=vec3(.2)*spec;
	
	FragColor.xyz = vec3(ambient+diffuse2+specular);
}