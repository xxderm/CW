#include "GUITexture.h"

GUITexture::GUITexture()
{

}

void GUITexture::Add(GuiFormat* format)
{	
	mGuis.push_back(format);
}

std::list<GuiFormat*> GUITexture::getGui()
{
	return mGuis;
}

void GUITexture::Clear()
{
	for (auto& gui : mGuis)
	{
		delete gui;
		gui = nullptr;
	}
	mGuis.clear();
}

GUITexture::~GUITexture()
{
	Clear();
}
