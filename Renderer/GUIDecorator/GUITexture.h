#pragma once
#ifndef GUI_TEXTURE_HEADER
#define GUI_TEXTURE_HEADER
#include "GUIDecorator.h"

class GUITexture final : public GUIDecorator
{
public:
	GUITexture(GUIRenderer* guiRenderer);
};

#endif // !GUITEXTURE_HEADER
