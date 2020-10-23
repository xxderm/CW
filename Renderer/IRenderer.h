#pragma once	
#ifndef IRENDERER_HEADER
#define IRENDERER_HEADER
#include "../Scene/SceneExt/Camera.h"
#include "../Scene/SceneExt/MousePicker.h"
#include "RenderExt/Text.h"

class IRenderer abstract
{
public:
	virtual void Init(SDL_Window* wnd) = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void setCamera(Camera* camera) = 0;
	virtual void setMousePicker(MousePicker* mp) = 0;
	virtual void HandleEvent(SDL_Event* e, SDL_Window* wnd) = 0;
};

#endif // !IRENDERER_HEADER
