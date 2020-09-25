#pragma once
#ifndef BUFFER_HEADER
#define BUFFER_HEADER
#include "RendererDecorator.h"

class Buffer abstract : public RendererDecorator
{
public:
	Buffer(Renderer* renderer);
	virtual void Set() = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
};

#endif // !BUFFER_HEADER
