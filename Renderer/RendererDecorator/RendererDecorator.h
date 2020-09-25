#pragma once
#ifndef RENDERER_DECORATOR_HEADER
#define RENDERER_DECORATOR_HEADER
#include "../Renderer.h"

class RendererDecorator : public Renderer
{
public:
	RendererDecorator(Renderer* renderer);
protected:
	Renderer* mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
