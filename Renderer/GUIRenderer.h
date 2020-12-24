#pragma once
#ifndef GUI_RENDERER_HEADER
#define GUI_RENDERER_HEADER
#include "IRenderer.h"
#include "../Reader.h"
#include "../Command/UICommand.h"
#include "../Scene/CountrySelectScene.h"
#include "../Command/ServerCommand.h"

class GUIRenderer : public IRenderer
{
public:
	GUIRenderer(std::string uiPath, int fontSize = 24, Scene* scene = nullptr, World* world = nullptr);
	void Render() override;
	void Init(SDL_Window* wnd) override;
	void Update() override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override; 
	void HandleEvent(SDL_Event* e, SDL_Window* wnd) override;

private:
	glm::mat4 CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale);
	void Listen();
private:
	std::unique_ptr<BufferObject> mQuad;
	std::unique_ptr<Shader> mProgram;
	std::unique_ptr<GUITexture> mGuis;
	Text mText;
	int mWinX, mWinY;
	int mMouseX, mMouseY;
	glm::vec2 mFormDistanceDifference = glm::vec2(-2);

	std::string mUiPath;
	int mFontSize = 24;

	Scene* mScene_ptr;
	World* mWorld_ptr = nullptr;
	CountryFormat mCountry_ptr;
	std::unordered_map<std::string, Command*> mCommand;

	std::vector<Lobby> mLobbies;
};

#endif // !GUIRENDERER_HEADER
