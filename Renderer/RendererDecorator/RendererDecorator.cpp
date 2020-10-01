#include "RendererDecorator.h"

RendererDecorator::RendererDecorator(Renderer* renderer)
	: mRenderer(renderer)
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
