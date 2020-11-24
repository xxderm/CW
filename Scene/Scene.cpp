#include "Scene.h"
INITIALIZE_EASYLOGGINGPP

Scene::Scene()
	: mWindow(nullptr), mRunning(false)
{
}

void Scene::Init()
{
	std::ifstream Config("Resources/config.json");
	if (not Config.is_open())
		LOG(ERROR) << "Failed to open file: Resources/config.json";
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(Config, pt);
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
		LOG(ERROR) << "Failed to init SDL";

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, pt.get<int>("CONTEXT_MAJOR_VERSION"));
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, pt.get<int>("CONTEXT_MINOR_VERSION"));
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	mWindow = SDL_CreateWindow(
		"Course of War", 
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		pt.get<int>("SCREEN_WIDTH"),
		pt.get<int>("SCREEN_HEIGHT"),
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
	);
	if(mWindow == nullptr)
		LOG(ERROR) << "Failed to create window";
	mContext = SDL_GL_CreateContext(mWindow);
	if (glewInit() != GLEW_OK)
		LOG(ERROR) << "Failed to init glew";
	
	Config.close();
	mRunning = true;


	this->mIPv4 = pt.get<std::string>("SERVER IPv4");
	this->mPort = pt.get<Uint16>("SERVER PORT");
	this->Connect();

	/*glClearDepth(1.f);
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT | GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);*/


	glEnable(GL_PRIMITIVE_RESTART);
	glPrimitiveRestartIndex(0xFFFF);
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

void Scene::Listen()
{
	mScenes.back()->Listen(this);
}

void Scene::Response()
{
	mScenes.back()->Response(this);
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

SDL_Window* Scene::getWindow()
{
	return mWindow;
}

SDL_GLContext Scene::getContext()
{
	return mContext;
}

SDL_Event* Scene::getEvent()
{
	return &mEvent;
}

bool Scene::isRunning()
{
	return mRunning;
}

void Scene::Exit()
{
	this->mRunning = false;
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
