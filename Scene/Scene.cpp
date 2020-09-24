#include "Scene.h"

Scene::Scene()
	: mWindow(nullptr), mRunning(false)
{
}

void Scene::Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	mWindow = SDL_CreateWindow(
		"CW", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		1024, 768, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	mContext = SDL_GL_CreateContext(mWindow);
	if (glewInit() != GLEW_OK)
		;// log

	mRunning = true;
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

void Scene::Quit()
{
	mRunning = false;
}

const SDL_Window* Scene::getWindow()
{
	return mWindow;
}

const SDL_GLContext Scene::getContext()
{
	return mContext;
}

const SDL_Event* Scene::getEvent()
{
	return mEvent;
}

bool Scene::isRunning()
{
	return mRunning;
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
