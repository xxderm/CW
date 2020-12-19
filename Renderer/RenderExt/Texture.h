#pragma once
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
#include "../../stb_image.h"
#include <string>
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <map>
#include <fstream>
#include "easylogging++.h"

enum class Parameter
{
	NONE,
	CTG,
	NEAREST_CTG,
	LINEAR
};

class Texture final 
{
public:
	Texture();
	stbi_uc* Add(std::string path, int format = GL_RGBA, int activeTexture = -1, Parameter param = Parameter::NONE, bool mipmaps = true, bool mfree = true);
	char* AddCache(glm::vec2 size, std::string path, int format = GL_RGBA, int activeTexture = -1, Parameter param = Parameter::NONE, bool mipmaps = true, bool mfree = true, std::string srcPath = "");
	void LoadCubemap(std::initializer_list<std::string> faces, int activeTexture);
	const glm::vec2 getSize(unsigned int id);
	~Texture();
private:
	std::map<unsigned int, glm::vec2>* mTexture = nullptr;
};

#endif // !TEXTURE_HEADER
