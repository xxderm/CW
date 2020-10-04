#pragma once
#ifndef DRAWABLE_ADAPTER_HEADER
#define DRAWABLE_ADAPTER_HEADER
#include "RenderExtensionDecorator.h"

template<class Decoration>
class DrawableAdapter : public RendererExtensionDecorator, public Decoration
{
public:
	DrawableAdapter(std::unique_ptr<IRenderExtension> rendExt);
	void Create() override;
};

#endif // !DRAWABLE_ADAPTER_HEADER

template<class Decoration>
inline DrawableAdapter<Decoration>::DrawableAdapter(std::unique_ptr<IRenderExtension> rendExt)
	: RendererExtensionDecorator{ std::move(rendExt) }
{
}

template<class Decoration>
void DrawableAdapter<Decoration>::Create()
{
	RendererExtensionDecorator::Create();
	Decoration::Draw();
}