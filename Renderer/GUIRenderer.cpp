#include "GUIRenderer.h"

void GUIRenderer::Render()
{
	mProgram->Bind();
	for (auto& gui : mGuis->getGui())
	{
		mProgram->setMat4("transformationMatrix", 
			CreateTransformationMatrix(gui->Position, gui->Scale));
		mProgram->setInt("guiTexture", gui->TextureId);
		mProgram->setVec4("guiColor", gui->Color);
		if (gui->TextureId == -1)
			mProgram->setBool("TextureMode", 0);
		else
			mProgram->setBool("TextureMode", 1);
		mQuad->Draw(GL_TRIANGLE_STRIP, 8);
	}
	mProgram->UnBind();
}

void GUIRenderer::Init()
{
	mProgram = std::make_unique<Shader>("Shaders/GUIVertex.glsl", "Shaders/GUIFragment.glsl");
	mProgram->Bind();
	mQuad = std::make_unique<BufferObject>();
	mQuad->Set(Vertices.data(), nullptr, Indices.data(), GL_STATIC_DRAW, sizeof(glm::vec3) * Vertices.size(), 0, sizeof(GLuint) * Indices.size());
	mQuad->UnBind();
	mProgram->UnBind();

	mGuis = std::make_unique<GUITexture>();
}

void GUIRenderer::Update()
{
	Reader::getInstance()->getUI(mGuis.get(), "Resources/UI/Main.ui");
}

void GUIRenderer::setCamera(Camera* camera)
{
}

void GUIRenderer::setMousePicker(MousePicker* mp)
{
}

void GUIRenderer::HandleEvent(SDL_Event* e)
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
