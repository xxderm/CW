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