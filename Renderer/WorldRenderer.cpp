#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(unsigned char* colorDataPtr, World* worldPtr)
{
	mFocusRGB = new unsigned char[3];
	mFocusRGB = colorDataPtr;
	mWorld = worldPtr;
}

void WorldRenderer::Render()
{
	mFbo->Bind();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mProgram[ShaderType::FBO_PROVINCE]->Bind();
	mProgram[ShaderType::FBO_PROVINCE]->setMat4("mvp", mvp);
	glBindTexture(GL_TEXTURE_2D, 17);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	{
		int mx, my; float zf;
		SDL_GetMouseState(&mx, &my);
		GLint vp[4];
		GLdouble mv[16];
		GLdouble pr[16];
		glGetIntegerv(GL_VIEWPORT, vp);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv);
		glGetDoublev(GL_PROJECTION_MATRIX, pr);
		GLfloat zc;
		GLfloat wy = (float)vp[3] - float(my);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glReadPixels(mx, wy, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, mFocusRGB);
	}	
	mProgram[ShaderType::FBO_PROVINCE]->UnBind();

	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgram[ShaderType::WATER]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[ShaderType::WATER]->UnBind();

	mProgram[ShaderType::TERRAIN]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[ShaderType::TERRAIN]->UnBind();
	mFbo->UnBind();
	


	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	

	// Рендер земли 
	mProgram[ShaderType::WORLD]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[ShaderType::WORLD]->UnBind();
}

void WorldRenderer::Update()
{
	static float dudv = 0;
	dudv += 0.00015f;
	dudv = fmod(dudv, 1.0f);
	mvp = projection * mCamera->getViewMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	mProgram[ShaderType::WATER]->Bind();
	mProgram[ShaderType::WATER]->setMat4("model", glm::make_mat4(modelview));
	mProgram[ShaderType::WATER]->setMat4("mvp", mvp);
	mProgram[ShaderType::WATER]->setFloat("time", dudv);
	mProgram[ShaderType::WATER]->setFloat("moveFactor", dudv);
	mProgram[ShaderType::WATER]->setVec3("cameraPos", mCamera->getPosition());
	mProgram[ShaderType::WATER]->setInt("TerrainFBO", 17);
	mProgram[ShaderType::WATER]->UnBind();

	mProgram[ShaderType::TERRAIN]->Bind();
	mProgram[ShaderType::TERRAIN]->setMat4("model", glm::make_mat4(modelview));
	mProgram[ShaderType::TERRAIN]->setMat4("mvp", mvp);
	mProgram[ShaderType::TERRAIN]->setVec3("campos", mCamera->getPosition());
	
	mProgram[ShaderType::TERRAIN]->setFloat("time", dudv);
	mProgram[ShaderType::TERRAIN]->setInt("TerrainFBO", 17);
	static float Time = 0.0;
	Time += 0.05;
	mProgram[ShaderType::TERRAIN]->setFloat("Tick", Time);
	//mProgram[ShaderType::TERRAIN]->setVec3("hoverEffect", glm::vec3(mFocusRGB[0], mFocusRGB[1], mFocusRGB[2]));
	mProgram[ShaderType::TERRAIN]->UnBind();

	mProgram[ShaderType::WORLD]->Bind();
	mProgram[ShaderType::WORLD]->setMat4("model", glm::make_mat4(modelview));
	mProgram[ShaderType::WORLD]->setMat4("mvp", mvp);
	mProgram[ShaderType::WORLD]->setFloat("time", dudv * 5.8);
	mProgram[ShaderType::WORLD]->setVec3("campos", mCamera->getPosition());
	mProgram[ShaderType::WORLD]->setInt("terrain", 17);
	mProgram[ShaderType::WORLD]->UnBind();
	//printf("%d, %d, %d\n", mFocusRGB[0], mFocusRGB[1], mFocusRGB[2]);
}

void WorldRenderer::Init(SDL_Window* wnd)
{	
	SDL_GetWindowSize(wnd, &mWinX, &mWinY);
	projection = glm::perspective<float>(45.f, float((float)mWinX / (float)mWinY), 0.1, 100.f);
	this->TerrainInit();
	this->WorldInit();


	mFbo = std::make_unique<FrameBuffer>();
	mFbo->Set(GL_COLOR_ATTACHMENT0, glm::vec2(mWinX, mWinY), GL_TEXTURE17);
	mProgram[ShaderType::FBO_PROVINCE] = std::make_unique<Shader>("Shaders/ProvinceVertex.glsl", "Shaders/ProvinceFragment.glsl", "Shaders/ProvinceTessControl.glsl", "Shaders/ProvinceTessEval.glsl");
	mProgram[ShaderType::FBO_PROVINCE]->Bind();
	mBuffer->Bind();
	mProgram[ShaderType::FBO_PROVINCE]->setInt("currentDraw", 1);
	mProgram[ShaderType::FBO_PROVINCE]->setInt("prov", 9);
	mProgram[ShaderType::FBO_PROVINCE]->setInt("terrain", 0);
	mProgram[ShaderType::FBO_PROVINCE]->setInt("Countries", 2);
	mBuffer->UnBind();
	mProgram[ShaderType::FBO_PROVINCE]->UnBind();
}

void WorldRenderer::setCamera(Camera* camera)
{
	mCamera = camera;
}

void WorldRenderer::setMousePicker(MousePicker* mp)
{
}

void WorldRenderer::HandleEvent(SDL_Event* e, SDL_Window* wnd)
{
	if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_F1)
		{
			mProgram[ShaderType::TERRAIN]->Bind();
			mProgram[ShaderType::TERRAIN]->setInt("currentDraw", 0);
			mProgram[ShaderType::TERRAIN]->UnBind();
			mProgram[ShaderType::FBO_PROVINCE]->Bind();
			mProgram[ShaderType::FBO_PROVINCE]->setInt("currentDraw", 1);
			mProgram[ShaderType::FBO_PROVINCE]->UnBind();
		}
		if (e->key.keysym.sym == SDLK_F2)
		{
			mProgram[ShaderType::TERRAIN]->Bind();
			mProgram[ShaderType::TERRAIN]->setInt("currentDraw", 1);
			mProgram[ShaderType::TERRAIN]->UnBind();
			mProgram[ShaderType::FBO_PROVINCE]->Bind();
			mProgram[ShaderType::FBO_PROVINCE]->setInt("currentDraw", 1);
			mProgram[ShaderType::FBO_PROVINCE]->UnBind();
		}
		if (e->key.keysym.sym == SDLK_F3)
		{
			mProgram[ShaderType::TERRAIN]->Bind();
			mProgram[ShaderType::TERRAIN]->setInt("currentDraw", 2);
			mProgram[ShaderType::TERRAIN]->UnBind();
		}
	}
}

void WorldRenderer::TerrainInit()
{
	Vertices.resize(25600);
	TexCoord.resize(25600);
	Indices.resize(32000);
	std::ifstream data;
	data.open("Resources/cache/vmapdata", std::ios::binary);
	if (data.is_open())
	{
		data.read((char*)Vertices.data(), 25600 * sizeof(glm::vec3));
		data.close();
		data.open("Resources/cache/tmapdata", std::ios::binary);
		data.read((char*)TexCoord.data(), 25600 * sizeof(glm::vec2));
		data.close();
		data.open("Resources/cache/imapdata", std::ios::binary);
		data.read((char*)Indices.data(), 32000 * sizeof(GLuint));
		data.close();
	}
	else
	{
		Vertices.clear();
		TexCoord.clear();
		Indices.clear();
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
	}


	mProgram[ShaderType::TERRAIN] = std::make_unique<Shader>("Shaders/TerrainVertex.glsl", "Shaders/TerrainFragment.glsl", "Shaders/TerrainTessControl.glsl", "Shaders/TerrainTessEval.glsl");
	mProgram[ShaderType::TERRAIN]->Bind();
	mBuffer = std::make_unique<BufferObject>();
	mBuffer->Set(Vertices.data(), TexCoord.data(), Indices.data(), GL_STATIC_DRAW, sizeof(glm::vec3) * Vertices.size(), sizeof(glm::vec2) * TexCoord.size(), sizeof(GLuint) * Indices.size());
	mTexture = std::make_unique<Texture>();



	mTexture->AddCache(
		glm::vec2(5632,2048),
		"Resources/cache/ht",
		GL_RGB, GL_TEXTURE0, Parameter::NONE, true, true,
		"Resources/terrain/ht.bmp");
	mProgram[ShaderType::TERRAIN]->setInt("terrain", 0);

	mTexture->AddCache(
		glm::vec2(5632, 2048),
		"Resources/cache/countries",
		GL_RGB, GL_TEXTURE2,
		Parameter::LINEAR);
	mProgram[ShaderType::TERRAIN]->setInt("Countries", 2);


	
	this->InitTextures("Resources/terrain texture.json");

	for (auto& texture : mTextures)
	{
		if (texture->Program == 0)
		{
			mTexture->Add(
				texture->Size,
				mTextureDatas.at(texture->Name),
				texture->Format, texture->ID,
				texture->Param
			);
			mProgram[ShaderType::TERRAIN]->setInt(texture->UniformName, texture->UniformID);
		}
	}
	
	mBuffer->UnBind();
	mProgram[ShaderType::TERRAIN]->UnBind();


	mProgram[ShaderType::WATER] = std::make_unique<Shader>(
		"Shaders/WaterVertex.glsl",
		"Shaders/WaterFragment.glsl",
		"Shaders/WaterTessControl.glsl",
		"Shaders/WaterTessEval.glsl");
	mProgram[ShaderType::WATER]->Bind();
	mBuffer->Bind();
	mProgram[ShaderType::WATER]->setFloat("speed", 0.14f);
	mProgram[ShaderType::WATER]->setFloat("amount", 990.000101f);
	mProgram[ShaderType::WATER]->setFloat("height", 0.001);
	mTexture->LoadCubemap(
		{ "Resources/terrain/cubemap/right.jpg",
		"Resources/terrain/cubemap/left.jpg",
		"Resources/terrain/cubemap/up.jpg",
		"Resources/terrain/cubemap/down.jpg",
		"Resources/terrain/cubemap/front.jpg",
		"Resources/terrain/cubemap/back.jpg" },
		GL_TEXTURE15
	);
	mProgram[ShaderType::WATER]->setInt("skybox", 15);
	for (auto& texture : mTextures)
	{
		if (texture->Program == 1)
		{
			mTexture->Add(
				texture->Size,
				mTextureDatas.at(texture->Name),
				texture->Format, texture->ID,
				texture->Param
			);
			mProgram[ShaderType::WATER]->setInt(texture->UniformName, texture->UniformID);
		}
	}
	mBuffer->UnBind();
	mProgram[ShaderType::WATER]->UnBind();
}

void WorldRenderer::WorldInit()
{
	mProgram[ShaderType::WORLD] = std::make_unique<Shader>(
		"Shaders/WorldVertex.glsl",
		"Shaders/WorldFragment.glsl",
		"Shaders/WorldTessControl.glsl",
		"Shaders/WorldTessEval.glsl");
	mProgram[ShaderType::WORLD]->Bind();
	mBuffer->Bind();
	mBuffer->UnBind();
	mProgram[ShaderType::WORLD]->UnBind();
}

void WorldRenderer::AsyncLoadTexture(std::string Path, std::string TextureName)
{
	mThreads.push_back(new boost::thread([this](std::string path, std::string name)
	{
		mTextureDatas.emplace(name, stbi_load(path.c_str(), &mTextureX, &mTextureY, &mTextureChanel, 0));
	}, Path, TextureName));
	textureLoadThreads.add_thread(mThreads.back());
}
