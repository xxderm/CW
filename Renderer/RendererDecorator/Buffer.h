#pragma once
#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "RendererDecorator.h"

class Buffer abstract
{
public:
	Buffer();
private:
	virtual void Create(const char* fboName) = 0;
	virtual void Bind(const char* fboName) = 0;
	virtual void UnBind(const char* fboName) = 0;
};

#endif // !BUFFER_HEADER
