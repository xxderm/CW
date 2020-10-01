#pragma once
#include "Scene.h"
#ifndef GAME_SCENE_HEADER
#define GAME_SCENE_HEADER
#include "../Renderer/Renderer.h"
#include "../Renderer/GUIRenderer.h"
#include "../Renderer/WorldRenderer.h"
#include "../Renderer/RendererDecorator/FrameBuffer.h"
#include "../Renderer/RendererDecorator/BufferObject.h"
#include "../Renderer/RendererDecorator/Shader.h"
#include "../Renderer/RendererDecorator/Texture.h"
#include "../Renderer/RendererDecorator/GUITexture.h"

class GameScene : public SceneMachine
{
public:
	void Init(Scene* scene) override;
	void Clean() override;
	void Pause() override;
	void Resume() override;
	void HandleEvents(Scene* scene) override;
	void Update(Scene* scene) override;
	void Draw(Scene* scene) override;
	static GameScene* getInstance()
	{
		return &mGameScene;
	}
	~GameScene();
protected:
	GameScene();
private:
	static GameScene mGameScene;
	std::unique_ptr<Renderer> mGuiRenderer;
	std::unique_ptr<Renderer> mWorldRenderer;
};

#endif // !GAMESCENE_HEADER
