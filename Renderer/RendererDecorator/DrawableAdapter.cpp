#include "DrawableAdapter.h"

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
