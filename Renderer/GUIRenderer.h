#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "IGUIRenderer.h"

class GUIRenderer : public Renderer, public IGUIRenderer
{
public:
	void Render() override;
	void Create() override;
	void Init() override;
private:
};

#endif // !GUIRENDERER_HEADER
