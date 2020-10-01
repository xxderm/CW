#include "RendererDecorator.h"

RendererDecorator::RendererDecorator(std::unique_ptr<Renderer> renderer)
	: mRenderer{ std::move(renderer) }
{
}

void RendererDecorator::Init()
{
	mRenderer->Init();
}

void RendererDecorator::Render()
{
	mRenderer->Render();
}
