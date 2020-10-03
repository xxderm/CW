#pragma once
#ifndef FRAME_BUFFER_HEADER
#define FRAME_BUFFER_HEADER
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

class FrameBuffer final
{
public:
	FrameBuffer();
	void Create(const char* fboName);
	void Bind(const char* fboName);
	void UnBind(const char* fboName);
	void Set(const char* fboName, int attachment_id, glm::vec2 scr, int texActiveId = -1, bool blend = 0);
private:
	std::map<std::string, GLuint> mFboID;
	GLuint mTextureID;
	GLuint mRboID;
};

#endif // !FRAMEBUFFER_HEADER
