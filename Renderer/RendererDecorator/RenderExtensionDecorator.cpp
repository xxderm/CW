#include "RenderExtensionDecorator.h"

RendererExtensionDecorator::RendererExtensionDecorator(std::unique_ptr<IRenderExtension> renderer)
	: mRenderer{ std::move(renderer) }
{
}

void RendererExtensionDecorator::Create()
{
	mRenderer->Create();
}
