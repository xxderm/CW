#pragma once
#ifndef BUFFER_HEADER
#define BUFFER_HEADER
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

struct Mesh
{
	std::string Name;
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> TexCoord;
	std::vector<GLuint> Indices;
	GLuint DrawType;
};

class Buffer abstract
{
public:
	virtual void Init() = 0;
	virtual void Bind(const char* name) = 0;
	virtual void UnBind(const char* name) = 0;
};

#endif // !BUFFER_HEADER
