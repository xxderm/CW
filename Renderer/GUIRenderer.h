#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "Renderer.h"

class GUIRenderer : public Renderer
{
public:
	void Render() override;
	void Init() override;
private:
};

#endif // !GUIRENDERER_HEADER
