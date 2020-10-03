#pragma once
#ifndef RENDER_EXTENSION_DECORATOR_HEADER
#define RENDER_EXTENSION_DECORATOR_HEADER
#include "../IRenderExtension.h"

class RendererExtensionDecorator : public IRenderExtension
{
public:
	RendererExtensionDecorator(std::unique_ptr<IRenderExtension> renderer);
	void Create() override;
protected:
	std::unique_ptr<IRenderExtension> mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
