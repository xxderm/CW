#include "GUITexture.h"

GUITexture::GUITexture(GUIRenderer* guiRenderer)
	: GUIDecorator(guiRenderer)
{
}

void GUITexture::Add(int texId, glm::vec2 pos, glm::vec2 scale)
{
	GuiFormat*tmp = new GuiFormat();
	tmp->TextureId = texId;
	tmp->Position = pos;
	tmp->Scale = scale;
	tmp->Box.x = pos.x - scale.x;
	tmp->Box.w = pos.x + scale.x;
	tmp->Box.y = pos.y + scale.y;
	tmp->Box.z = pos.y - scale.y;
	mGuis.push_back(tmp);
}

const std::list<GuiFormat*> GUITexture::getGui()
{
	return mGuis;
}

GUITexture::~GUITexture()
{
	for (auto& gui : mGuis)
	{
		delete gui;
		gui = nullptr;
	}
}
