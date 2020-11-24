#pragma once
#ifndef MENU_SCENE_HEADER
#define MENU_SCENE_HEADER
#include "Scene.h"
#include "../Renderer/GUIRenderer.h"

class MenuScene final : public SceneMachine
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
	static MenuScene* getInstance()
	{
		return &mMenuScene;
	}
	~MenuScene();
protected:
	MenuScene();
private:
	static MenuScene mMenuScene;

	IRenderer* mGUIRenderer = nullptr;

	MousePicker* mMousePicker = nullptr;
	Camera* mCamera = nullptr;

	int mWndWidth;
	int mWndHeight;
	int mMouseX;
	int mMouseY;
};

#endif // !MENU_SCENE_HEADER
