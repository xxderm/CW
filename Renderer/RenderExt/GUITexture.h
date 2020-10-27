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

struct GuiFormat
{
	const bool isHovered(glm::vec2 mouse);
	int TextureId = -1;
	glm::vec2 Position;
	glm::vec2 Scale;
	std::string Name;
	glm::vec4 Box;
	std::unordered_map<std::string, std::pair<glm::vec2, glm::vec4>> Text;
	glm::vec4 Color = glm::vec4(1, 1, 1, 0.5);
	glm::vec4 hoverColor = glm::vec4(1, 1, 1, 0.5);
	bool Visible = true;
};

class GUITexture final
{
public:	
	GUITexture();
	void Add(std::string Name, GuiFormat *format);
	std::unordered_map<std::string, GuiFormat*> getGui();
	void Clear();
	~GUITexture();
private:
	std::unordered_map<std::string, GuiFormat*> mGuis;
};

#endif // !GUITEXTURE_HEADER
