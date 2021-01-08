#pragma once	
#ifndef IRENDERER_HEADER
#define IRENDERER_HEADER
#include "../Scene/SceneExt/Camera.h"
#include "../Scene/SceneExt/MousePicker.h"
#include "RenderExt/Texture.h"
#include "RenderExt/FrameBuffer.h"
#include "RenderExt/Text.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <fstream>

class IRenderer abstract
{
public:
	virtual void Init(SDL_Window* wnd) = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
	virtual void setCamera(Camera* camera) = 0;
	virtual void setMousePicker(MousePicker* mp) = 0;
	virtual void HandleEvent(SDL_Event* e, SDL_Window* wnd) = 0;
protected:
	void InitTextures(std::string manifest);
	void AsyncLoadTexture(std::string Path,	std::string TextureName);
	int mTextureX, mTextureY, mTextureChanel;
	boost::thread_group textureLoadThreads;
	boost::mutex mThreadMutex;
	std::unordered_map<std::string, stbi_uc*> mTextureDatas;
	std::vector<boost::thread*> mThreads;
	std::vector<TextureFormat*> mTextures;
};

#endif // !IRENDERER_HEADER
