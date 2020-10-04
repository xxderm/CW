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
	mWorldRenderer = new WorldRenderer();
	mWorldRenderer->Init();	
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
	
}

void GameScene::Draw(Scene* scene)
{	
	mWorldRenderer->Render();
	SDL_GL_SwapWindow(scene->getWindow());
}

