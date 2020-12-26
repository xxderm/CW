#pragma once
#ifndef GUI_TEXTURE_HEADER
#define GUI_TEXTURE_HEADER
#include <string>
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <map>
#include <fstream>
#include "easylogging++.h"
#include "Text.h"

struct GuiFormat
{
	const bool isHovered(glm::vec2 mouse);
	int TextureId = -1;
	glm::vec2 Position;
	glm::vec2 Scale;
	std::string Name;
	glm::vec4 Box;
	std::unordered_map<std::string, Str> Text;
	glm::vec4 Color = glm::vec4(1, 1, 1, 0.5);
	glm::vec4 hoverColor = glm::vec4(1, 1, 1, 0.5);
	bool Visible = true;
	std::string Type;
	std::string For;
	std::vector<std::string> ShowToClick;
	std::vector<std::string> HideToClick;
	std::pair<bool, SDL_Keycode> Key = std::make_pair<bool, SDL_Keycode>(false, ' ');	
	std::pair<std::string, std::vector<std::string>> CommandOnClick;
	bool ActiveHighlight = false;
	float ActiveHighlightIntensity = 1.0;
	int LobbyIndex = -1;
	bool DynamicText = false;
	std::string SelectedCountryTag;
	bool Moveable = false;
	std::string Parent;

	glm::vec2 Padding;

	glm::vec4 baseColor = glm::vec4(1, 1, 1, 0.5);
	bool Active = false;
	bool DebugElement = false;
};

class GUITexture final
{
public:	
	GUITexture();
	void Add(std::string Name, GuiFormat *format, bool insertBegin = false);
	std::vector < std::pair<std::string, GuiFormat*> > getGui();
	GuiFormat* Get(std::string Name);
	void SetVisible(std::string Name, bool v);
	void SetColor(std::string Name, glm::vec4 Color);
	void ShareChildsVisible(std::string Parent, bool visible);
	bool isAllInputHidden();
	void DeactivateAll();
	void DeactivateAll(std::string formName);
	void Clear();
	~GUITexture();
private:
	std::vector<std::pair<std::string, GuiFormat*>> mGuis;
};

#endif // !GUITEXTURE_HEADER
