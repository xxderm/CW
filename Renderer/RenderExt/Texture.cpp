#include "Texture.h"

Texture::Texture()	
{
	mTexture = new std::map<unsigned int, glm::vec2>();
}

void Texture::Add(std::string path, int format, int activeTexture)
{
	glm::vec2 size;
	int x, y;
	int chnls;
	auto textureData = stbi_load(path.c_str(), &x, &y, &chnls, 0);
	size = glm::vec2(x, y);
	unsigned int textureId;
	if (activeTexture != -1)
	{
		glActiveTexture(activeTexture);
		textureId = activeTexture;
	}
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, (int)size.x, (int)size.y, 0, format, GL_UNSIGNED_BYTE, textureData);
	stbi_image_free(textureData);
	mTexture->emplace(textureId, size);
}

const glm::vec2 Texture::getSize(unsigned int id)
{
	if (mTexture->count(id) > 0)
		return mTexture->at(id);
	LOG(ERROR) << "Texture not found";
	throw std::exception();
}
