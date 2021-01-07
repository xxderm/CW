#pragma once
#ifndef TEXT_HEADER
#define TEXT_HEADER
#include "Shader.h"
#include "BufferObject.h"
#include <map>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <SDL.h>
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character final
{
	GLuint TextureID;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	GLuint Advance;
};

enum TextAnchor
{
	LEFT,
	RIGHT,
	CENTER,
	NONE
};

struct Str final
{
	std::string Text;
	glm::vec2 Position;
	glm::vec4 Color;
	float Scale = 1.0;
	float BaseScale = 1.0;
	TextAnchor Anchor = TextAnchor::NONE;
};

class Text final
{
public:
	void Init(const char* font, glm::vec2 scrSize, GLuint fontSize = 12);
	// Возвращает координату `х` последнего символа
	int RenderText(std::string text, int x, int y, float scale, glm::vec4 color);
	void Resize(glm::vec2 scrSize);
private:
	std::map<char, Character> mCharacters;
	std::unique_ptr<Shader> mProgram;
	std::unique_ptr<BufferObject> mObject;
	glm::mat4 proj;
};

#endif