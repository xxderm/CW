#include "CountrySelectScene.h"

CountrySelectScene CountrySelectScene::mCountryScene;

void CountrySelectScene::Init(Scene* scene)
{
	mWorld = new World();
	std::thread th(&World::Create, mWorld);
	th.detach();

	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);

	mFocusCountryPtr = new unsigned char[3];
	mWorldRenderer = new WorldRenderer(mFocusCountryPtr);
	mGUIRenderer = new GUIRenderer("Resources/UI/country select.ui.json", 24, scene, mWorld);

	mWorldRenderer->Init(scene->getWindow());
	mGUIRenderer->Init(scene->getWindow());

	mCamera = new Camera(glm::vec3(68.72f, 10.83f, 18.34f));
	mCamera->setUp(glm::vec3(-0.0, 0.344642, -0.938734));
	mCamera->setRight(glm::vec3(1.0, 0.0, -0.00));
	mCamera->setFront(glm::vec3(-0.0, -0.938734, -0.344642));
	mMousePicker = new MousePicker(glm::vec2(128, 50), glm::vec2(mWndWidth, mWndHeight));

	mWorldRenderer->setCamera(mCamera);
	mWorldRenderer->setMousePicker(mMousePicker);

	mGUIRenderer->setCamera(mCamera);
	mGUIRenderer->setMousePicker(mMousePicker);

	scene->getUser()->setStatus(UserState::COUNTRY_SELECT);
}

void CountrySelectScene::Clean()
{
}

void CountrySelectScene::Pause()
{
}

void CountrySelectScene::Resume()
{
}

void CountrySelectScene::HandleEvents(Scene* scene)
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
		mWorldRenderer->HandleEvent(scene->getEvent(), scene->getWindow());

		if (scene->getEvent()->type == SDL_MOUSEBUTTONDOWN)
		{
			auto selectedCountry = mWorld->getCountries()->getCountryByColor( 
				std::to_string(int(mFocusCountryPtr[0])) +
				std::to_string(int(mFocusCountryPtr[1])) +
				std::to_string(int(mFocusCountryPtr[2])));
			if (selectedCountry)
				scene->getUser()->setCountry(selectedCountry);
		}
		mGUIRenderer->HandleEvent(scene->getEvent(), scene->getWindow());
	}
}

void CountrySelectScene::Update(Scene* scene)
{
	SDL_GetMouseState(&mMouseX, &mMouseY);
	if (mMouseX >= mWndWidth - 10 && mMouseX <= mWndWidth - 1)
		mCamera->ProcessKeyboard(Camera_Movement::CRIGHT, 0.08);
	if (mMouseX <= 10 && mMouseX >= 1)
		mCamera->ProcessKeyboard(Camera_Movement::CLEFT, 0.08);
	if (mMouseY >= mWndHeight - 10 && mMouseY <= mWndHeight - 1)
		mCamera->ProcessKeyboard(Camera_Movement::ZBOTTOM, 0.08);
	if (mMouseY <= 10 && mMouseY >= 1)
		mCamera->ProcessKeyboard(Camera_Movement::ZTOP, 0.01);

	mWorldRenderer->Update();
	mGUIRenderer->Update();
}

void CountrySelectScene::Draw(Scene* scene)
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	glViewport(0, 0, mWndWidth, mWndHeight);
	mWorldRenderer->Render();
	mGUIRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

void CountrySelectScene::Listen(Scene* scene)
{
}

void CountrySelectScene::Response(Scene* scene)
{
}

CountrySelectScene::~CountrySelectScene()
{
}

CountrySelectScene::CountrySelectScene()
{
}
