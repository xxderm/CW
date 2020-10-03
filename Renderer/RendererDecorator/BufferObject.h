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

struct BufferObjectFormat
{
	unsigned int VboID[3];
	unsigned int VaoID;
};

class BufferObject final
{
public:
	BufferObject();
	void Create(const char* fboName);
	void Bind(const char* fboName);
	void UnBind(const char* fboName);
	void Set(
		const char* fboName,
		void* vertices,
		void* texCoord,
		void* indices,
		GLuint draw_type,
		GLuint vert_size,
		GLuint texCoordSize,
		GLuint ind_size,
		int d = 3);
	void Draw(const char* fboName, GLuint type, GLsizei count);
	const unsigned getVaoID(const char* fboName);
	~BufferObject();
private:
	std::map<std::string, BufferObjectFormat> mBufferObj;
};

#endif // !BUFFEROBJECT_HEADER
