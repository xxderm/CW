#pragma once
#ifndef BUFFER_OBJECT_HEADER
#define BUFFER_OBJECT_HEADER
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

class BufferObject final
{
public:
	BufferObject();
	void Bind();
	void UnBind();
	void Draw(GLuint type, GLsizei count);
	const unsigned getVaoID();
	~BufferObject();
	void Set(
		void* vertices,
		void* texCoord,
		void* indices,
		GLuint draw_type,
		GLuint vert_size,
		GLuint texCoordSize,
		GLuint ind_size,
		int d = 3,
		int ap = 0);
	void Update(void* vertices, GLuint size);
	unsigned int VboID[3];
private:
	unsigned int VaoID;
};

#endif // !BUFFEROBJECT_HEADER
