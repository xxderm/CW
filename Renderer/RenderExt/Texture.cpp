#include "Texture.h"

Texture::Texture()	
{
	mTexture = new std::map<unsigned int, glm::vec2>();
}

void Texture::Add(std::string path, int format, int activeTexture, Parameter param)
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
	switch (param)
	{
	case Parameter::NONE:
		break;
	case Parameter::CTG:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case Parameter::NEAREST_CTG:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_WRAP_S), GL_CLAMP_TO_EDGE);
		glTexParameteri(GLenum(GL_TEXTURE_2D), GLenum(GL_TEXTURE_WRAP_T), GL_CLAMP_TO_EDGE);
		break;
	case Parameter::LINEAR:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		break;
	default:
		break;
	}
	glGenerateMipmap(GL_TEXTURE_2D);
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
