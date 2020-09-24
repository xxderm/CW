#include "Scene.h"
INITIALIZE_EASYLOGGINGPP

Scene::Scene()
	: mWindow(nullptr), mRunning(false)
{
}
#include <iostream>
void Scene::Init()
{
	std::ifstream Config("Resources/config.json");
	if (not Config.is_open())
		LOG(ERROR) << "Failed to open file: Resources/config.json";
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(Config, pt);
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, pt.get<int>("CONTEXT_MAJOR_VERSION"));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, pt.get<int>("CONTEXT_MINOR_VERSION"));
	mWindow = SDL_CreateWindow(
		"Course of War", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		pt.get<int>("SCREEN_WIDTH"),
		pt.get<int>("SCREEN_HEIGHT"),
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	mContext = SDL_GL_CreateContext(mWindow);
	if (glewInit() != GLEW_OK)
		;// log
	
	Config.close();
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
