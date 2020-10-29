#include "GUIRenderer.h"

void GUIRenderer::Render()
{		
	for (auto& gui : mGuis->getGui())
	{
		if (gui.second->Visible)
		{
			mProgram->Bind();
			mProgram->setMat4("transformationMatrix",
				CreateTransformationMatrix(gui.second->Position, gui.second->Scale));
			mProgram->setInt("guiTexture", gui.second->TextureId);
			mProgram->setVec4("guiColor", gui.second->Color);
			if (gui.second->TextureId == -1)
				mProgram->setBool("TextureMode", 0);
			else
				mProgram->setBool("TextureMode", 1);
			mQuad->Draw(GL_TRIANGLE_STRIP, 8);
			mProgram->UnBind();	

			glDisable(GL_DEPTH_TEST);
			for (auto& text : gui.second->Text)
				mText.RenderText(
					text.second.Text,
					text.second.Position.x,
					text.second.Position.y,
					1,
					glm::vec4(text.second.Color));
			glEnable(GL_DEPTH_TEST);
		}
	}
}

void GUIRenderer::Init(SDL_Window* wnd)
{
	mProgram = std::make_unique<Shader>("Shaders/GUIVertex.glsl", "Shaders/GUIFragment.glsl");
	mProgram->Bind();
	mQuad = std::make_unique<BufferObject>();
	float Vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	int Indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	mQuad->Set(Vertices, nullptr, Indices, GL_STATIC_DRAW, 4 * 8, 0, 4 * 8, 2);
	mQuad->UnBind();
	mProgram->UnBind();

	mGuis = std::make_unique<GUITexture>();

	
	SDL_GetWindowSize(wnd, &mWinX, &mWinY);
	mText.Init("Resources/font/17541.ttf", glm::vec2(mWinX, mWinY), 24);
	Reader::getInstance()->getUI(mGuis.get(), "Resources/UI/Main.ui");
}

void GUIRenderer::Update()
{
	//Reader::getInstance()->getUI(mGuis.get(), "Resources/UI/Main.ui");
}

void GUIRenderer::setCamera(Camera* camera)
{
}

void GUIRenderer::setMousePicker(MousePicker* mp)
{
}

void GUIRenderer::HandleEvent(SDL_Event* e, SDL_Window* wnd)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (mGuis->Get("ConsoleInput")->Visible
			&& (e->key.keysym.sym != SDLK_LSHIFT && e->key.keysym.sym != SDLK_LALT && e->key.keysym.sym != SDLK_BACKQUOTE) )
		{
			// erase last sym
			if (e->key.keysym.sym == SDLK_BACKSPACE && mGuis->Get("ConsoleInput")->Text.at("Input").Text.size() > 0)
				mGuis->Get("ConsoleInput")->Text.at("Input").Text
				.erase(mGuis->Get("ConsoleInput")->Text.at("Input").Text.end() - 1);
			// add sym
			else 
				mGuis->Get("ConsoleInput")->Text.at("Input").Text += e->key.keysym.sym;
		}
		if (e->key.keysym.sym == SDLK_BACKQUOTE)
		{
			mGuis->SetVisible("ConsoleInput", !mGuis->Get("ConsoleInput")->Visible);
			mGuis->SetVisible("ConsoleForm", !mGuis->Get("ConsoleForm")->Visible);
			mGuis->Get("ConsoleInput")->Text.at("Input").Text.clear();
		}
	}
}

glm::mat4 GUIRenderer::CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix =
		glm::identity<glm::mat4>();
	matrix *= glm::translate(glm::vec3(translation.x, translation.y, 0));
	matrix *= glm::scale(glm::vec3(scale.x, scale.y, 1.f));
	return matrix;
}
