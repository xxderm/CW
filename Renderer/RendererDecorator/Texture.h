#pragma once
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
#include "../../stb_image.h"
#include "RenderExtensionDecorator.h"

class Texture final : public RendererExtensionDecorator
{
public:
	Texture(std::unique_ptr<IRenderExtension> rendExt);
	void Create() override;
	void Use(char* Name) override;
private:
	void Add(std::string path, int format = GL_RGBA,int activeTexture = -1);
	const glm::vec2 getSize(unsigned int id);
private:
	std::map<unsigned int, glm::vec2> mTexture;
};

#endif // !TEXTURE_HEADER
