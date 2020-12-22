#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "IRenderer.h"
#include "RenderExt/Texture.h"
#include "RenderExt/FrameBuffer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include "../World/World.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class WorldRenderer final : public IRenderer
{
public:
	WorldRenderer(unsigned char* colorDataPtr = nullptr);
	void Render() override;
	void Update() override;
	void Init(SDL_Window* wnd) override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override;
	void HandleEvent(SDL_Event* e, SDL_Window* wnd) override;
private:
	void TerrainInit();
	void CloudsInit();
	void AsyncLoadTexture(std::string Path, std::string TextureName);
private:
	std::unique_ptr<Shader> mProgram[4];
	std::unique_ptr<Texture> mTexture;
	std::unique_ptr<BufferObject> mBuffer;
	std::unique_ptr<FrameBuffer> mFbo;
	Camera* mCamera;

private:
	GLdouble modelview[16];
	GLuint mTexId = 0;
	glm::mat4x4 mvp;
	unsigned char* mFocusRGB;
private:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> TexCoord;
	std::vector<GLuint> Indices;
	glm::mat4x4 projection;

	boost::mutex mThreadMutex;
	int mTextureX, mTextureY, mTextureChanel;
	boost::thread_group textureLoadThreads;
	std::unordered_map<std::string, stbi_uc*> mTextureDatas;
	std::vector<boost::thread*> mThreads;
	std::vector<TextureFormat*> mTextures;

	//stbi_uc* texData;
	//stbi_uc* provData;
	//World world;
};

#endif // !WORLDRENDERER_HEADER
