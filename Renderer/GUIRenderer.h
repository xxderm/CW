#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "IRenderer.h"
#include "../Reader.h"

class GUIRenderer : public IRenderer
{
public:
	void Render() override;
	void Init(SDL_Window* wnd) override;
	void Update() override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override; 
	void HandleEvent(SDL_Event* e, SDL_Window* wnd) override;

private:
	glm::mat4 CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
private:
	std::unique_ptr<BufferObject> mQuad;
	std::unique_ptr<Shader> mProgram;
	std::unique_ptr<GUITexture> mGuis;
	Text mText;
};

#endif // !GUIRENDERER_HEADER
