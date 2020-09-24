#pragma once
#ifndef SCENE_HEADER
#define SCENE_HEADER
#include <list>

class SceneMachine;

class Scene
{
public:
	Scene();
	void Init();
	void ChangeScene(SceneMachine* scene);
	void PushScene(SceneMachine* scene);
	void PopScene();
	void HandleEvents();
	void Update();
	void Draw();
	void Clean();
	void Quit();
private:
	std::list<SceneMachine*> mScenes;
};

class SceneMachine
{
public:
	SceneMachine();
	virtual void Init(Scene* scene) = 0;
	virtual void Clean() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;
	virtual void HandleEvents(Scene* scene) = 0;
	virtual void Update(Scene* scene) = 0;
	virtual void Draw(Scene* scene) = 0;
	void ChangeScene(Scene* scene, SceneMachine* sceneMachine);
	virtual ~SceneMachine();
};

#endif // !SCENE_HEADER
