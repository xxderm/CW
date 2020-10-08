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
	unsigned int TextureId;
	glm::vec2 Position;
	glm::vec2 Scale;
	std::string Name;
	glm::vec4 Box;
};

class GUITexture final
{
public:	
	GUITexture();
	void Add(int texId, glm::vec2 pos, glm::vec2 scale);
	const std::list<GuiFormat*> getGui();
	~GUITexture();
private:
	std::list<GuiFormat*> mGuis;
};

#endif // !GUITEXTURE_HEADER
