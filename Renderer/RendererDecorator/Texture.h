#pragma once
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
#include "RendererDecorator.h"
#include "../../stb_image.h"

class Texture final : public RendererDecorator
{
public:
	Texture(std::unique_ptr<Renderer> renderer);
	void Init() override;
	void Render() override;
	void Update() override;
	void AddTexture(std::string path, int format = GL_RGBA,int activeTexture = -1);
	const glm::vec2 getSize(unsigned int id);
	void Use(const char* Name) override;
private:
	std::map<unsigned int, glm::vec2> mTexture;
};

#endif // !TEXTURE_HEADER
