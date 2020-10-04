#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "IRenderer.h"
#include "RendererDecorator/Texture.h"
#include "RendererDecorator/Shader.h"
#include "RendererDecorator/DrawableAdapter.h"
#include "RendererDecorator/BindingAdapter.h"
#include "RendererDecorator/FrameBuffer.h"
#include "RendererDecorator/BufferObject.h"

class WorldRenderer final : public IRenderer
{
public:
	void Render() override;
	void Update() override;
	void Init() override;
private:
	std::initializer_list<std::pair<char*, bool>> mShaders;
	std::vector<Mesh> mMesh;
	Mesh TerrainMesh;
};

#endif // !WORLDRENDERER_HEADER
