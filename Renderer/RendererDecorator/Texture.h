#pragma once
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
#include "RendererDecorator.h"
#include "../../stb_image.h"

class Texture final : public RendererDecorator
{
public:
	Texture(Renderer* renderer);
	void Init() override;
private:
	void AddTexture(std::string path, int format = GL_RGBA,int activeTexture = -1);
	const glm::vec2 getSize(unsigned int id);
private:
	std::map<unsigned int, glm::vec2> mTexture;
};

#endif // !TEXTURE_HEADER
