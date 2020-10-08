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
	void setCamera(Camera* camera);
	void setMousePicker(MousePicker* mp); 
private:
};

#endif // !GUIRENDERER_HEADER
