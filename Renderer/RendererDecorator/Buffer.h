#pragma once
#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "SDL.h"
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include "RendererDecorator.h"

class Buffer abstract
{
public:
	Buffer();
	virtual void Create() = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
};

#endif // !BUFFER_HEADER
