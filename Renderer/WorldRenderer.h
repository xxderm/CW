#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "IRenderer.h"
#include "RenderExt/Texture.h"
#include "RenderExt/Shader.h"
#include "RenderExt/FrameBuffer.h"
#include "RenderExt/BufferObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

class WorldRenderer final : public IRenderer
{
public:
	void Render() override;
	void Update() override;
	void Init() override;
	void setCamera(Camera* camera) override;
	void setMousePicker(MousePicker* mp) override;
	void HandleEvent(SDL_Event* e) override;
private:
	void TerrainInit();
	void WaterInit();
private:
	std::unique_ptr<Shader> mProgram[2];
	std::unique_ptr<Texture> mTexture;
	std::unique_ptr<BufferObject> mBuffer;
	Camera* mCamera;

private:
	GLdouble modelview[16];


private:
	std::vector<glm::vec3> Vertices;
	std::vector<glm::vec2> TexCoord;
	std::vector<GLuint> Indices;
	glm::mat4x4 projection;
};

#endif // !WORLDRENDERER_HEADER
