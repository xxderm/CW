#include "GUITexture.h"

GUITexture::GUITexture()
{

}

void GUITexture::Add(std::string Name, GuiFormat* format)
{	
	mGuis.emplace(Name, format);
}

std::unordered_map<std::string, GuiFormat*> GUITexture::getGui()
{
	return mGuis;
}

void GUITexture::Clear()
{
	for (auto& gui : mGuis)
	{
		delete gui.second;
		gui.second = nullptr;
	}
	mGuis.clear();
}

GUITexture::~GUITexture()
{
	Clear();
}

const bool GuiFormat::isHovered(glm::vec2 mouse)
{
	auto xmin = Position.x - Scale.x;
	auto xmax = Position.x + Scale.x;
	auto ymin = Position.y + Scale.y;
	auto ymax = Position.y - Scale.y;
	if (
		(mouse.x >= (xmin) &&
			mouse.x <= (xmax)) &&
		(mouse.y <= ymin && mouse.y >= ymax)
		)
	{
		return true;
	}
	return false;
}
