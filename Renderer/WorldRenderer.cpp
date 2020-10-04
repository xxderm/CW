#include "WorldRenderer.h"

void WorldRenderer::Render()
{
}

void WorldRenderer::Update()
{
}

void WorldRenderer::Init()
{
	mShaders = {
		std::pair<char*, bool>((char*)"GUI", false),
		std::pair<char*, bool>((char*)"Province", true),
		std::pair<char*, bool>((char*)"Terrain", true),
		std::pair<char*, bool>((char*)"Water", true)
	};
	Mesh TerrainMesh;
	TerrainMesh.Name = "Terrain";
	for (size_t y = 0; y < 50; y++)
	{
		for (size_t x = 0; x < 128; x++)
		{
			TerrainMesh.Vertices.push_back(glm::vec3(x, 0, y));
			TerrainMesh.TexCoord.push_back(glm::vec2(TerrainMesh.Vertices.back().x, TerrainMesh.Vertices.back().z));
			TerrainMesh.Indices.push_back(TerrainMesh.Vertices.size() - 1);

			TerrainMesh.Vertices.push_back(glm::vec3(x + 1, 0, y));
			TerrainMesh.TexCoord.push_back(glm::vec2(TerrainMesh.Vertices.back().x, TerrainMesh.Vertices.back().z));
			TerrainMesh.Indices.push_back(TerrainMesh.Vertices.size() - 1);

			TerrainMesh.Vertices.push_back(glm::vec3(x + 1, 0, y + 1));
			TerrainMesh.TexCoord.push_back(glm::vec2(TerrainMesh.Vertices.back().x, TerrainMesh.Vertices.back().z));
			TerrainMesh.Indices.push_back(TerrainMesh.Vertices.size() - 1);

			TerrainMesh.Vertices.push_back(glm::vec3(x, 0, y + 1));
			TerrainMesh.Indices.push_back(TerrainMesh.Vertices.size() - 1);
			TerrainMesh.TexCoord.push_back(glm::vec2(TerrainMesh.Vertices.back().x, TerrainMesh.Vertices.back().z));
			TerrainMesh.Indices.push_back(0xFFFF);
		}
	}
	mMesh.push_back(TerrainMesh);

	//mRenderExtension = std::make_unique<DrawableAdapter<BufferObject>>(std::move(mRenderExtension));
	//mRenderExtension = std::make_unique<BindingAdapter<FrameBuffer>>(std::move(mRenderExtension));
	mRenderExtension = std::make_unique<RenderExtension>();
	mRenderExtension = std::make_unique<Texture>(std::move(mRenderExtension));
	mRenderExtension = std::make_unique<BindingAdapter<Shader>>(std::move(mRenderExtension));
	static_cast<BindingAdapter<Shader>*>(mRenderExtension.get())->setShaderNames(mShaders);
	mRenderExtension = std::make_unique<BindingAdapter<BufferObject>>(std::move(mRenderExtension));	
	static_cast<BindingAdapter<BufferObject>*>(mRenderExtension.get())->setMesh(mMesh);
	mRenderExtension->Create();
}
