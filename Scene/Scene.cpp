#include "Scene.h"

Scene::Scene()
{
}

void Scene::Init()
{

}

void Scene::ChangeScene(SceneMachine* scene)
{
	if (not mScenes.empty())
	{
		mScenes.back()->Clean();
		mScenes.back()->Init(this);
	}
	mScenes.push_back(scene);
	mScenes.back()->Init(this);
}

void Scene::PushScene(SceneMachine* scene)
{
	if (not mScenes.empty())
		mScenes.back()->Pause();
	mScenes.push_back(scene);
	mScenes.back()->Init(this);
}

void Scene::PopScene()
{
	if (not mScenes.empty())
	{
		mScenes.back()->Clean();
		mScenes.pop_back();
		mScenes.back()->Resume();
	}	
}

void Scene::HandleEvents()
{
	mScenes.back()->HandleEvents(this);
}

void Scene::Update()
{
	mScenes.back()->Update(this);
}

void Scene::Draw()
{
	mScenes.back()->Draw(this);
}

void Scene::Clean()
{
	while (not mScenes.empty())
	{
		mScenes.back()->Clean();
		mScenes.pop_back();
	}
}

SceneMachine::SceneMachine()
{
}

void SceneMachine::ChangeScene(Scene* scene, SceneMachine* sceneMachine)
{
	scene->ChangeScene(sceneMachine);
}

SceneMachine::~SceneMachine()
{
}
