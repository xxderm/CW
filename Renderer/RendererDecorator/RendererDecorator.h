#pragma once
#ifndef RENDERER_DECORATOR_HEADER
#define RENDERER_DECORATOR_HEADER
#include "../Renderer.h"

class RendererDecorator : public Renderer
{
public:
	RendererDecorator(Renderer* renderer);
	void Init() override;
	void Render() override;
protected:
	Renderer* mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
