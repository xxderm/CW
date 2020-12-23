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

GuiFormat* GUITexture::Get(std::string Name)
{
	return mGuis.at(Name);
}

void GUITexture::SetVisible(std::string Name, bool v)
{
	this->mGuis.at(Name)->Visible = v;
}

void GUITexture::SetColor(std::string Name, glm::vec4 Color)
{
	this->mGuis.at(Name)->Color = Color;
}

bool GUITexture::isAllInputHidden()
{
	for (auto& i : mGuis)
	{
		if (i.second->Type == "Input" && (i.second->Visible && i.second->Active))
			return false;
	}
	return true;
}

void GUITexture::Clear()
{
	for (auto& gui : mGuis)
	{
		gui.second->Text.clear();
		gui.second->ShowToClick.clear();
		gui.second->HideToClick.clear();
		gui.second->CommandOnClick.second.clear();

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
