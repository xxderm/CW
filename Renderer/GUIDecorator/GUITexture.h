#pragma once
#ifndef GUI_TEXTURE_HEADER
#define GUI_TEXTURE_HEADER
#include "GUIDecorator.h"

struct GuiFormat
{
	unsigned int TextureId;
	glm::vec2 Position;
	glm::vec2 Scale;
	std::string Name;
	glm::vec4 Box;
};

class GUITexture final : public GUIDecorator
{
public:	
	GUITexture(std::unique_ptr<IGUIRenderer> guiRenderer);
	void Create() override;
	void Add(int texId, glm::vec2 pos, glm::vec2 scale);
	const std::list<GuiFormat*> getGui();
	~GUITexture();
private:
	std::list<GuiFormat*> mGuis;
};

#endif // !GUITEXTURE_HEADER
