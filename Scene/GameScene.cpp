#include "GameScene.h"

GameScene GameScene::mGameScene;

GameScene::~GameScene()
{
}

GameScene::GameScene()
{
}

void GameScene::Init(Scene* scene)
{		
	SDL_GetWindowSize(scene->getWindow(), &mWndWidth, &mWndHeight);
	lastX = mWndWidth / 2;
	lastY = mWndHeight / 2;
	mCamera = new Camera(glm::vec3(0.f, 0.f, 3.f));
	mMousePicker = new MousePicker(glm::vec2(128, 50), glm::vec2(mWndWidth, mWndHeight));
	
	mWorldRenderer = new WorldRenderer();
	mWorldRenderer->Init();	
	mWorldRenderer->setCamera(mCamera);
	mWorldRenderer->setMousePicker(mMousePicker);
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
		if (scene->getEvent()->key.keysym.sym == SDLK_w)
		{
			mCamera->ProcessKeyboard(CFORWARD, 0.16f);
		}
		if (scene->getEvent()->key.keysym.sym == SDLK_s)
		{
			mCamera->ProcessKeyboard(CBACKWARD, 0.16f);
		}
		if (scene->getEvent()->key.keysym.sym == SDLK_a)
		{
			mCamera->ProcessKeyboard(CLEFT, 0.16f);
		}
		if (scene->getEvent()->key.keysym.sym == SDLK_d)
		{
			mCamera->ProcessKeyboard(CRIGHT, 0.16f);
		}

		static bool buttonPressed = false;
		static bool firstMouse = true;
		if (scene->getEvent()->type == SDL_MOUSEBUTTONDOWN)
			buttonPressed = true;
		if (scene->getEvent()->type == SDL_MOUSEBUTTONUP)
		{
			buttonPressed = false;
			firstMouse = true;
		}
		if (buttonPressed)
		{
			int xpos, ypos;
			SDL_GetMouseState(&xpos, &ypos);
			if (firstMouse)
			{
				lastX = xpos;
				lastY = ypos;
				firstMouse = false;
			}
			GLfloat xoffset = xpos - lastX;
			GLfloat yoffset = lastY - ypos;
			lastX = xpos;
			lastY = ypos;
			mCamera->ProcessMouseMovement(xoffset, yoffset);
		}
	}
}

void GameScene::Update(Scene* scene)
{

}

void GameScene::Draw(Scene* scene)
{		
	mWorldRenderer->Render();		
	SDL_GL_SwapWindow(scene->getWindow());
}

