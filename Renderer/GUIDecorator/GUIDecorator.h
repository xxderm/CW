#pragma once
#ifndef GUI_DECORATOR_HEADER
#define GUI_DECORATOR_HEADER
#include "../IGUIRenderer.h"

class GUIDecorator : public IGUIRenderer
{
public:
	GUIDecorator(std::unique_ptr<IGUIRenderer> guiRenderer);
	void Create() override;
protected:
	std::unique_ptr<IGUIRenderer> mGUIRenderer;
};

#endif // !GUIDECORATOR_HEADER
