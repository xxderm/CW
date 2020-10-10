#include "WorldRenderer.h"

void WorldRenderer::Render()
{
	glClearColor(0.1, 0.1, 0.1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4x4 mvp = projection * mCamera->getViewMatrix();
	GLdouble modelview[16];
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	mProgram->Bind();
	mProgram->setMat4("model", glm::make_mat4(modelview));
	mProgram->setMat4("mvp", mvp);
	mProgram->setVec3("campos", mCamera->getPosition());
	mProgram->setFloat("time", 0.1);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());	
	mProgram->UnBind();	
}

void WorldRenderer::Update()
{
}

void WorldRenderer::Init()
{	
	projection = glm::perspective<float>(45.f, float((float)1280 / (float)720), 0.01, 100.f);
	for (size_t y = 0; y < 50; y++)
	{
		for (size_t x = 0; x < 128; x++)
		{
			Vertices.push_back(glm::vec3(x, 0, y));
			TexCoord.push_back(glm::vec2(Vertices.back().x, Vertices.back().z));
			Indices.push_back(Vertices.size() - 1);

			Vertices.push_back(glm::vec3(x + 1, 0, y));
			TexCoord.push_back(glm::vec2(Vertices.back().x, Vertices.back().z));
			Indices.push_back(Vertices.size() - 1);

			Vertices.push_back(glm::vec3(x + 1, 0, y + 1));
			TexCoord.push_back(glm::vec2(Vertices.back().x, Vertices.back().z));
			Indices.push_back(Vertices.size() - 1);

			Vertices.push_back(glm::vec3(x, 0, y + 1));
			Indices.push_back(Vertices.size() - 1);
			TexCoord.push_back(glm::vec2(Vertices.back().x, Vertices.back().z));
			Indices.push_back(0xFFFF);
		}
	}
	mProgram = new Shader("Shaders/TerrainVertex.glsl", "Shaders/TerrainFragment.glsl", "Shaders/TerrainTessControl.glsl", "Shaders/TerrainTessEval.glsl");
	mProgram->Bind();
	mBuffer = new BufferObject();
	mBuffer->Set(Vertices.data(), TexCoord.data(), Indices.data(), GL_STATIC_DRAW, sizeof(glm::vec3) * Vertices.size(), sizeof(glm::vec2) * TexCoord.size(), sizeof(GLuint) * Indices.size());
	mTexture = new Texture();

	mTexture->Add(
		"Resources/terrain/ht.bmp",
		GL_RGB, GL_TEXTURE0);
	mProgram->setInt("terrain", 0);

	mTexture->Add(
		"Resources/terrain/terrain24.bmp",
		GL_RGB, GL_TEXTURE1,
		Parameter::NEAREST_CTG);
	mProgram->setInt("terrain_map", 1);

	mTexture->Add(
		"Resources/terrain/Countrymap.png",
		GL_RGBA, GL_TEXTURE2,
		Parameter::LINEAR);
	mProgram->setInt("Countries", 2);

	mTexture->Add(
		"Resources/terrain/atlas0.bmp",
		GL_RGB, GL_TEXTURE3,
		Parameter::CTG);
	mProgram->setInt("TerrainTextureID", 3);

	mTexture->Add(
		"Resources/terrain/countryborder.png",
		GL_RGBA, GL_TEXTURE4,
		Parameter::CTG);
	mProgram->setInt("countryborder", 4);

	mTexture->Add(
		"Resources/terrain/Blank_province_map.png",
		GL_RGBA, GL_TEXTURE5,
		Parameter::NEAREST_CTG);
	mProgram->setInt("province_border", 5);

	mTexture->Add(
		"Resources/terrain/tb24.bmp",
		GL_RGB, GL_TEXTURE6,
		Parameter::NEAREST_CTG);
	mProgram->setInt("terra", 6);

	mTexture->Add(
		"Resources/terrain/World_normal.png",
		GL_RGBA, GL_TEXTURE7,
		Parameter::LINEAR);
	mProgram->setInt("wn", 7);

	mTexture->Add(
		"Resources/terrain/atlas_normal0.bmp",
		GL_RGB, GL_TEXTURE8,
		Parameter::LINEAR);
	mProgram->setInt("an", 8);

	mTexture->Add(
		"Resources/terrain/provinces.bmp",
		GL_RGB, GL_TEXTURE9,
		Parameter::NEAREST_CTG);
	mProgram->setInt("provinces", 9);

	mProgram->UnBind();
}

void WorldRenderer::setCamera(Camera* camera)
{
	mCamera = camera;
}

void WorldRenderer::setMousePicker(MousePicker* mp)
{
}
