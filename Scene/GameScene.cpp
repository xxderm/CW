#include "GameScene.h"

GameScene GameScene::mGameScene;

GameScene::~GameScene()
{
}

GameScene::GameScene()
{
}

GameScene::GameScene(IRenderer* Render)
{

}

void GameScene::Init(Scene* scene)
{		
	// TODO: Загружать страны в сцене выбора страны и перемещать указатель в сцену игры
	mWorld = new World();
	std::thread th(&World::Create, mWorld);
	th.detach();
	


	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	lastX = mWndWidth / 2;
	lastY = mWndHeight / 2;
	mCamera = new Camera(glm::vec3(68.72f, 10.83f, 18.34f));
	mCamera->setUp(glm::vec3(-0.0, 0.344642, -0.938734));
	mCamera->setRight(glm::vec3(1.0, 0.0, -0.00));
	mCamera->setFront(glm::vec3(-0.0, -0.938734, -0.344642));
	mMousePicker = new MousePicker(glm::vec2(128, 50), glm::vec2(mWndWidth, mWndHeight));
	
	if (!mWorldRenderer)
	{
		mFocusCountryPtr = new unsigned char[3];
		mWorldRenderer = new WorldRenderer(mFocusCountryPtr, mWorld);
		mWorldRenderer->Init(scene->getWindow());
		mWorldRenderer->setCamera(mCamera);
		mWorldRenderer->setMousePicker(mMousePicker);
	}

	mGUIRenderer = new GUIRenderer("Resources/UI/game.ui.json", 30, scene, mWorld);
	mGUIRenderer->Init(scene->getWindow());
	mGUIRenderer->setCamera(mCamera);
	mGUIRenderer->setMousePicker(mMousePicker);

	scene->getUser()->setStatus(UserState::PLAYING);

	/* DEBUG */
	scene->getUser()->setCountry(mWorld->getCountries()->getCountryByTag("SOV"));
}

void GameScene::Clean()
{
}

void GameScene::Pause()
{
}

void GameScene::Resume()
{
}

void GameScene::HandleEvents(Scene* scene)
{
	while (SDL_PollEvent(scene->getEvent()))
	{
		if (scene->getEvent()->type == SDL_MOUSEWHEEL)
		{
			if (scene->getEvent()->wheel.y > 0)
				mCamera->ProcessKeyboard(Camera_Movement::CFORWARD, 0.35);
			if (scene->getEvent()->wheel.y < 0)
				mCamera->ProcessKeyboard(Camera_Movement::CBACKWARD, 0.35);
		}
		mGUIRenderer->HandleEvent(scene->getEvent(), scene->getWindow());
		mWorldRenderer->HandleEvent(scene->getEvent(), scene->getWindow());
	}
}

void GameScene::Update(Scene* scene)
{
	SDL_GetMouseState(&mMouseX, &mMouseY);
	if (mMouseX >= mWndWidth - 10 && mMouseX <= mWndWidth - 1)
		mCamera->ProcessKeyboard(Camera_Movement::CRIGHT, 0.28);
	if (mMouseX <= 10 && mMouseX >= 1)
		mCamera->ProcessKeyboard(Camera_Movement::CLEFT, 0.28);
	if (mMouseY >= mWndHeight - 10 && mMouseY <= mWndHeight - 1)
		mCamera->ProcessKeyboard(Camera_Movement::ZBOTTOM, 0.28);
	if (mMouseY <= 10 && mMouseY >= 1)
		mCamera->ProcessKeyboard(Camera_Movement::ZTOP, 0.20);

	
	mWorldRenderer->Update();
	mGUIRenderer->Update();
}

void GameScene::Draw(Scene* scene)
{		
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	glViewport(0, 0, mWndWidth, mWndHeight);
	mWorldRenderer->Render();		
	mGUIRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

void GameScene::Listen(Scene* scene)
{
}

void GameScene::Response(Scene* scene)
{
	
}

