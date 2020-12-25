#include "GUITexture.h"

GUITexture::GUITexture()
{

}

void GUITexture::Add(std::string Name, GuiFormat* format, bool insertBegin)
{	
	if(!insertBegin)
		mGuis.push_back({ Name, format });
	else 
		mGuis.insert(mGuis.begin(), {Name, format});
}

std::vector < std::pair<std::string, GuiFormat*>> GUITexture::getGui()
{
	return mGuis;
}

GuiFormat* GUITexture::Get(std::string Name)
{
	for (auto& gui : mGuis)
	{
		if (gui.first == Name)
			return gui.second;
	}
	return nullptr;
}

void GUITexture::SetVisible(std::string Name, bool v)
{
	for (auto& gui : mGuis)
	{
		if (gui.first == Name)
			gui.second->Visible = v;
	}
}

void GUITexture::SetColor(std::string Name, glm::vec4 Color)
{
	for (auto& gui : mGuis)
	{
		if (gui.first == Name)
			gui.second->Color = Color;
	}
}

void GUITexture::ShareChildsVisible(std::string Parent, bool visible)
{
	for (auto& i : mGuis)
	{
		if (!i.second->Parent.empty())
			if (i.second->Parent == Parent)
				i.second->Visible = visible;
	}
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

void GUITexture::DeactivateAll()
{
	for (auto& i : mGuis)
	{
		if (i.second->Active)
			i.second->Active = false;
	}
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
