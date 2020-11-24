#pragma once
#ifndef GAME_SCENE_HEADER
#define GAME_SCENE_HEADER
#include "Scene.h"
#include "../Renderer/WorldRenderer.h"
#include "../Renderer/GUIRenderer.h"

class GameScene final : public SceneMachine
{
public:
	GameScene(IRenderer* Render);
	void Init(Scene* scene) override;
	void Clean() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(Scene* scene) override;
	void Update(Scene* scene) override;
	void Draw(Scene* scene) override;
	void Listen(Scene* scene) override;
	void Response(Scene* scene) override;
	static GameScene* getInstance()
	{
		return &mGameScene;
	}
	~GameScene();
protected:
	GameScene();
private:
	static GameScene mGameScene;	
	IRenderer* mWorldRenderer = nullptr;
	IRenderer* mGUIRenderer = nullptr;
	Camera* mCamera;
	MousePicker* mMousePicker;

	GLfloat lastX;
	GLfloat lastY;
	int mWndWidth, mWndHeight;
	int mMouseX, mMouseY;
};

#endif // !GAMESCENE_HEADER
