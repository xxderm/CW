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
					text.first,
					text.second.first.x,
					text.second.first.y,
					1,
					glm::vec4(text.second.second));
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
}

void GUIRenderer::Update()
{
	Reader::getInstance()->getUI(mGuis.get(), "Resources/UI/Main.ui");

	int mouseX, mouseY; 
	SDL_GetMouseState(&mouseX, &mouseY);	
	std::cout << mGuis->getGui().at("Test5")->isHovered(MousePicker::getNormalizedDeviceCoords(mouseX, mouseY, glm::vec2(mWinX, mWinY))) << std::endl;
}

void GUIRenderer::setCamera(Camera* camera)
{
}

void GUIRenderer::setMousePicker(MousePicker* mp)
{
}

void GUIRenderer::HandleEvent(SDL_Event* e, SDL_Window* wnd)
{
}

glm::mat4 GUIRenderer::CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix =
		glm::identity<glm::mat4>();
	matrix *= glm::translate(glm::vec3(translation.x, translation.y, 0));
	matrix *= glm::scale(glm::vec3(scale.x, scale.y, 1.f));
	return matrix;
}
