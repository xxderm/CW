#include "GameScene.h"

GameScene GameScene::mGameScene;

void GameScene::Init(Scene* scene)
{	
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
	SDL_GL_SwapWindow(scene->getWindow());
}

GameScene::GameScene()
{
}
