#include "BindingAdapter.h"

template<class Decoration>
inline BindingAdapter<Decoration>::BindingAdapter(std::unique_ptr<IRenderExtension> rendExt)
	: RendererExtensionDecorator{ std::move(rendExt) }
{
}

template<class Decoration>
void BindingAdapter<Decoration>::Create()
{
	RendererExtensionDecorator::Create();
	Decoration::Bind();
}
