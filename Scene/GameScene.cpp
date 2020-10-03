#include "GameScene.h"

GameScene GameScene::mGameScene;

GameScene::~GameScene()
{
}

GameScene::GameScene()
{
	mWorldRenderer = std::make_unique<WorldRenderer>();
	mWorldRenderer->Init();
	mGuiRenderer = std::make_unique<GUIRenderer>();
	mGuiRenderer->Init();
}

void GameScene::Init(Scene* scene)
{		
	mWorldRenderer = std::make_unique<Shader>(std::move(mWorldRenderer));
	mWorldRenderer = std::make_unique<BufferObject>(std::move(mWorldRenderer));
	mGuiRenderer = std::make_unique<Shader>(std::move(mGuiRenderer));
	mGuiRenderer = std::make_unique<BufferObject>(std::move(mGuiRenderer));

	mWorldRenderer->Init();
	mGuiRenderer->Init();
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
}

void GameScene::Update(Scene* scene)
{
	mWorldRenderer->Update();
	mGuiRenderer->Update();
}

void GameScene::Draw(Scene* scene)
{
	mWorldRenderer->Render();
	mGuiRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

