#pragma once
#ifndef COUNTRY_SELECT_SCENE
#define COUNTRY_SELECT_SCENE
#include "Scene.h"
#include "../Renderer/WorldRenderer.h"
#include "../Renderer/GUIRenderer.h"

class CountrySelectScene final : public SceneMachine
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
	static CountrySelectScene* getInstance()
	{
		return &mCountryScene;
	}
	~CountrySelectScene();
protected:
	CountrySelectScene();
private:
	static CountrySelectScene mCountryScene;

	IRenderer* mWorldRenderer = nullptr;
	IRenderer* mGUIRenderer = nullptr;

	MousePicker* mMousePicker = nullptr;
	Camera* mCamera = nullptr;

	int mWndWidth;
	int mWndHeight;
	int mMouseX;
	int mMouseY;
};

#endif // !COUNTRY_SELECT_SCENE
