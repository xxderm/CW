#include "IRenderer.h"

void IRenderer::InitTextures(std::string manifest)
{
	std::ifstream TextureConfig(manifest.c_str());
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(TextureConfig, pt);
	for (auto& array_element : pt)
	{
		mTextures.push_back(new TextureFormat());
		mTextures.back()->Name = array_element.first;
		mTextures.back()->ID = GL_TEXTURE0 + array_element.second.get<int>("ID");
		mTextures.back()->UniformID = array_element.second.get<int>("ID");
		mTextures.back()->Program = array_element.second.get<int>("Program");
		mTextures.back()->Path = array_element.second.get<std::string>("Path");
		if (array_element.second.get<std::string>("Format") == "RGBA")
			mTextures.back()->Format = GL_RGBA;
		else
			mTextures.back()->Format = GL_RGB;
		if (array_element.second.get<std::string>("Parameter") == "LINEAR")
			mTextures.back()->Param = Parameter::LINEAR;
		else if (array_element.second.get<std::string>("Parameter") == "CTG")
			mTextures.back()->Param = Parameter::CTG;
		else if (array_element.second.get<std::string>("Parameter") == "NEAREST_CTG")
			mTextures.back()->Param = Parameter::NEAREST_CTG;
		else if (array_element.second.get<std::string>("Parameter") == "NONE")
			mTextures.back()->Param = Parameter::NONE;
		mTextures.back()->UniformName = array_element.second.get<std::string>("UniformName");
		mTextures.back()->Size.x = array_element.second.get_child("Size").get<int>("x");
		mTextures.back()->Size.y = array_element.second.get_child("Size").get<int>("y");
	}

	for (auto& texture : mTextures)
		this->AsyncLoadTexture(texture->Path, texture->Name);
	this->textureLoadThreads.join_all();

	for (auto& thread : this->mThreads)
		this->textureLoadThreads.remove_thread(thread);
}

void IRenderer::AsyncLoadTexture(std::string Path, std::string TextureName)
{
	mThreads.push_back(new boost::thread([this](std::string path, std::string name)
		{
			mTextureDatas.emplace(name, stbi_load(path.c_str(), &mTextureX, &mTextureY, &mTextureChanel, 0));
		}, Path, TextureName));
	textureLoadThreads.add_thread(mThreads.back());
}
