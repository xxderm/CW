#pragma once
#ifndef RENDERERDECORATOR_HEADER
#define RENDERERDECORATOR_HEADER
#include "../Renderer.h"

class RendererDecorator : public Renderer
{
public:
	RendererDecorator(Renderer* renderer);
protected:
	Renderer* mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
