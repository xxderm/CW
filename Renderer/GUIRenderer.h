#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "IRenderer.h"

class GUIRenderer : public IRenderer
{
public:
	void Render() override;
	void Init() override;
	void Update() override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override; 
	void HandleEvent(SDL_Event* e) override;
private:
};

#endif // !GUIRENDERER_HEADER
