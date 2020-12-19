#include "Texture.h"

Texture::Texture()	
{
	mTexture = new std::map<unsigned int, glm::vec2>();
}

stbi_uc* Texture::Add(std::string path, int format, int activeTexture, Parameter param, bool mipmaps, bool mfree)
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
	if(mipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
	if(mfree)
		stbi_image_free(textureData);
	mTexture->emplace(textureId, size);

	if (textureData)
		return textureData;
	else
		return nullptr;
}

char* Texture::AddCache(glm::vec2 size, std::string path, int format, int activeTexture, Parameter param, bool mipmaps, bool mfree, std::string srcPath)
{
	int multiple = 3;
	if (format == GL_RGBA)
		multiple = 4;
	char* texData = new char[int(size.x) * int(size.y) * multiple];
	std::ifstream cache;
	cache.open(path, std::ios::in || std::ios::binary);
	if (!cache.is_open())
	{
		cache.close();

		int x, y, chnls;
		auto tdata = stbi_load(srcPath.c_str(), &x, &y, &chnls, 0);	
		std::ofstream save;
		save.open(path, std::ios::binary);
		save.write((char*)tdata, x * y * multiple);
		save.close();
		stbi_image_free(tdata);

		cache.open(path, std::ios::in || std::ios::binary);
	}
	cache.read((char*)texData, int(size.x) * int(size.y) * multiple);
	cache.close();


	unsigned int textureId;
	if (activeTexture != -1)
	{
		glActiveTexture(activeTexture);
		textureId = activeTexture;
	}
	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexImage2D(GL_TEXTURE_2D, 0, format, (int)size.x, (int)size.y, 0, format, GL_UNSIGNED_BYTE, texData);
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
	if (mipmaps)
		glGenerateMipmap(GL_TEXTURE_2D);
	if (mfree)
		delete[] texData;
	mTexture->emplace(textureId, size);

	if (texData)
		return texData;
	else
		return nullptr;
}

void Texture::LoadCubemap(std::initializer_list<std::string> faces, int activeTexture)
{
	glActiveTexture(activeTexture);
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	int index = 0;
	for (auto i : faces)
	{
		unsigned char* data = stbi_load(i.c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + index, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			LOG(ERROR) << "Cubemap texture failed to load at path: " << i;
			stbi_image_free(data);
			exit(1);
		}
		index++;
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	mTexture->emplace(textureID, glm::vec2(0, 0));
}

const glm::vec2 Texture::getSize(unsigned int id)
{
	if (mTexture->count(id) > 0)
		return mTexture->at(id);
	LOG(ERROR) << "Texture not found";
	throw std::exception();
}

Texture::~Texture()
{
	for (auto& i : *mTexture)
		glDeleteTextures(1, &i.first);
}
