#pragma once
#include "Scene.h"
#ifndef GAME_SCENE_HEADER
#define GAME_SCENE_HEADER

class GameScene : public SceneMachine
{
public:
	void Init(Scene* scene) override;
	void Clean() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(Scene* scene) override;
	void Update(Scene* scene) override;
	void Draw(Scene* scene) override;
	static GameScene* getInstance()
	{
		return &mGameScene;
	}
protected:
	GameScene();
private:
	static GameScene mGameScene;
};

#endif // !GAMESCENE_HEADER