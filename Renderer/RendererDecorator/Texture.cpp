#include "Texture.h"

Texture::Texture(Renderer* renderer)
	: RendererDecorator(renderer)
{
}

void Texture::Add(std::string path, int format, int activeTexture)
{
	glm::vec2 size;
	int chnls;
	auto textureData = stbi_load(path.c_str(), (int*)&size.x, (int*)&size.y, &chnls, 0);
	unsigned int textureId;
	if (activeTexture != -1)
	{
		glActiveTexture(activeTexture);
		textureId = activeTexture;
	}
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, (int)size.x, (int)size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
	stbi_image_free(textureData);
	mTexture.try_emplace(textureId, size);
}

const glm::vec2 Texture::getSize(unsigned int id)
{
	if (mTexture.count(id) > 0)
		return mTexture.at(id);
	LOG(ERROR) << "Failed to get texture size";
	throw std::exception();
}
