#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "Renderer.h"
#include "RendererDecorator/Shader.h"

class GUIRenderer : public Renderer
{
public:
	void Render() override;
	void Init() override;
	void Update() override;
protected:
	void Use(const char* Name) override;
private:
};

#endif // !GUIRENDERER_HEADER
