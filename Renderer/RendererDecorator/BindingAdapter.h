#pragma once
#ifndef BINDING_ADAPTER_HEADER
#define BINDING_ADAPTER_HEADER
#include "RenderExtensionDecorator.h"

template<class Decoration>
class BindingAdapter : public RendererExtensionDecorator, public Decoration
{
public:
	BindingAdapter(std::unique_ptr<IRenderExtension> rendExt);
	void Create() override;
};

#endif // !BINDING_ADAPTER_HEADER

template<class Decoration>
inline BindingAdapter<Decoration>::BindingAdapter(std::unique_ptr<IRenderExtension> rendExt)
	: RendererExtensionDecorator{ std::move(rendExt) }
{
}

template<class Decoration>
void BindingAdapter<Decoration>::Create()
{
	RendererExtensionDecorator::Create();
	Decoration::Init();
}