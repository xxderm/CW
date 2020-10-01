#include "GUIDecorator.h"

GUIDecorator::GUIDecorator(std::unique_ptr<IGUIRenderer> guiRenderer)
	: mGUIRenderer{ std::move(guiRenderer) }
{
}

void GUIDecorator::Create()
{
	mGUIRenderer->Create();
}
