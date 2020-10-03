#pragma once
#ifndef RENDERER_DECORATOR_HEADER
#define RENDERER_DECORATOR_HEADER
#include "../Renderer.h"

class RendererDecorator : public Renderer
{
public:
	RendererDecorator(std::unique_ptr<Renderer> renderer);
	void Init() override;
	void Render() override;
	void Update() override;
protected:
	void Use(const char* Name) override;
	std::unique_ptr<Renderer> mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
