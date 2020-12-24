#pragma once
#ifndef UI_DEBUG_SCENE_HEADER
#define UI_DEBUG_SCENE_HEADER
#include "Scene.h"
#include "../Renderer/GUIRenderer.h"

class UIDebugScene final : public SceneMachine
{
public:
	void Init(Scene* scene) override;
	void Clean() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(Scene* scene) override;
	void Update(Scene* scene) override;
	void Draw(Scene* scene) override;
	void Listen(Scene* scene) override;
	void Response(Scene* scene) override;
	static UIDebugScene* getInstance()
	{
		return &mDebugScene;
	}
	~UIDebugScene();
protected:
	UIDebugScene();
private:
	static UIDebugScene mDebugScene;


	IRenderer* mGUIRenderer = nullptr;

	MousePicker* mMousePicker = nullptr;
	Camera* mCamera = nullptr;

	int mWndWidth;
	int mWndHeight;
	int mMouseX;
	int mMouseY;
};

#endif // !UI_DEBUG_SCENE_HEADER
