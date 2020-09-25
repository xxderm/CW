#pragma once
#ifndef GUI_DECORATOR_HEADER
#define GUI_DECORATOR_HEADER
#include "../GUIRenderer.h"

class GUIDecorator : public GUIRenderer
{
public:
	GUIDecorator(GUIRenderer* guiRenderer);
protected:
	GUIRenderer* mGUIRenderer;
};

#endif // !GUIDECORATOR_HEADER
