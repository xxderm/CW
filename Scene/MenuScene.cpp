#include "MenuScene.h"

MenuScene MenuScene::mMenuScene;

void MenuScene::Init(Scene* scene)
{
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	mGUIRenderer = new GUIRenderer("Resources/UI/Menu.ui", 30, scene);

	mGUIRenderer->Init(scene->getWindow());

	mCamera = new Camera(glm::vec3(68.72f, 10.83f, 18.34f));
	mCamera->setUp(glm::vec3(-0.0, 0.344642, -0.938734));
	mCamera->setRight(glm::vec3(1.0, 0.0, -0.00));
	mCamera->setFront(glm::vec3(-0.0, -0.938734, -0.344642));
	mMousePicker = new MousePicker(glm::vec2(128, 50), glm::vec2(mWndWidth, mWndHeight));

	mGUIRenderer->setCamera(mCamera);
	mGUIRenderer->setMousePicker(mMousePicker);
}

void MenuScene::Clean()
{
}

void MenuScene::Pause()
{
}

void MenuScene::Resume()
{
}

void MenuScene::HandleEvents(Scene* scene)
{
	while (SDL_PollEvent(scene->getEvent()))
	{		
		mGUIRenderer->HandleEvent(scene->getEvent(), scene->getWindow());
	}
}

void MenuScene::Update(Scene* scene)
{
	mGUIRenderer->Update();
}

void MenuScene::Draw(Scene* scene)
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	glViewport(0, 0, mWndWidth, mWndHeight);
	mGUIRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

MenuScene::~MenuScene()
{
}

MenuScene::MenuScene()
{
}
