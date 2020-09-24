#pragma once
#include "Scene.h"
#ifndef GAMESCENE_HEADER
#define GAMESCENE_HEADER

class GameScene : public SceneMachine
{
public:
	void Init(Scene* state) override;
	void Clean() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(Scene* state) override;
	void Update(Scene* state) override;
	void Draw(Scene* state) override;
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
