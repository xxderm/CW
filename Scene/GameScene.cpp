#include "GameScene.h"

GameScene GameScene::mGameScene;

GameScene::~GameScene()
{
}

GameScene::GameScene()
{
	mWorldRenderer = std::make_unique<WorldRenderer>();
	mGuiRenderer = std::make_unique<GUIRenderer>();

	mWorldRenderer = std::make_unique<Texture>(std::move(mWorldRenderer));
	mWorldRenderer = std::make_unique<Shader>(std::move(mWorldRenderer));
	mWorldRenderer = std::make_unique<BufferObject>(std::move(mWorldRenderer));
	mWorldRenderer = std::make_unique<FrameBuffer>(std::move(mWorldRenderer));

	mGuiRenderer = std::make_unique<Texture>(std::move(mGuiRenderer));
	mGuiRenderer = std::make_unique<Shader>(std::move(mGuiRenderer));
	mGuiRenderer = std::make_unique<BufferObject>(std::move(mGuiRenderer));
	mGuiRenderer = std::make_unique<FrameBuffer>(std::move(mGuiRenderer));
	mGuiRenderer = std::make_unique<GUITexture>(std::move(mGuiRenderer));
	
}

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

