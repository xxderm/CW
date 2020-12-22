#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(unsigned char* colorDataPtr)
{
	mFocusRGB = new unsigned char[3];
	mFocusRGB = colorDataPtr;
}

void WorldRenderer::Render()
{
	mFbo->Bind();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mProgram[3]->Bind();
	mProgram[3]->setMat4("mvp", mvp);
	mProgram[3]->setInt("currentDraw", 1);
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
	mProgram[3]->UnBind();

	/*glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	mProgram[1]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[1]->UnBind();
	mProgram[0]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[0]->UnBind();*/
	mFbo->UnBind();


	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	mProgram[1]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[1]->UnBind();


	mProgram[0]->Bind();	
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());	
	mProgram[0]->UnBind();	

	/*mProgram[2]->Bind();
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	mBuffer->Draw(GL_PATCHES, Indices.size());
	mProgram[2]->UnBind();*/
}

void WorldRenderer::Update()
{
	static float dudv = 0;
	dudv += 0.00015f;
	dudv = fmod(dudv, 1.0f);
	mvp = projection * mCamera->getViewMatrix();
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	mProgram[1]->Bind();
	mProgram[1]->setMat4("model", glm::make_mat4(modelview));
	mProgram[1]->setMat4("mvp", mvp);
	mProgram[1]->setFloat("time", dudv);
	mProgram[1]->setFloat("moveFactor", dudv);
	mProgram[1]->setVec3("cameraPos", mCamera->getPosition());
	mProgram[1]->UnBind();

	mProgram[0]->Bind();
	mProgram[0]->setMat4("model", glm::make_mat4(modelview));
	mProgram[0]->setMat4("mvp", mvp);
	mProgram[0]->setVec3("campos", mCamera->getPosition());
	mProgram[0]->setFloat("time", dudv);
	static float Time = 0.0;
	Time += 0.05;
	mProgram[0]->setFloat("Tick", Time);
	//mProgram[0]->setVec3("hoverEffect", glm::vec3(mFocusRGB[0], mFocusRGB[1], mFocusRGB[2]));
	mProgram[0]->UnBind();

	mProgram[2]->Bind();
	mProgram[2]->setMat4("model", glm::make_mat4(modelview));
	mProgram[2]->setMat4("mvp", mvp);
	mProgram[2]->setFloat("time", dudv * 5.8);
	mProgram[2]->setVec3("campos", mCamera->getPosition());
	//mProgram[2]->setInt("terrain", 17);
	mProgram[2]->UnBind();
	//printf("%d, %d, %d\n", mFocusRGB[0], mFocusRGB[1], mFocusRGB[2]);
}

void WorldRenderer::Init(SDL_Window* wnd)
{	
	int w, h;
	SDL_GetWindowSize(wnd, &w, &h);
	projection = glm::perspective<float>(45.f, float((float)w / (float)h), 0.1, 100.f);
	this->TerrainInit();
	this->WaterInit();
	this->CloudsInit();


	mFbo = std::make_unique<FrameBuffer>();
	mFbo->Set(GL_COLOR_ATTACHMENT0, glm::vec2(w, h), GL_TEXTURE17);
	mProgram[3] = std::make_unique<Shader>("Shaders/ProvinceVertex.glsl", "Shaders/ProvinceFragment.glsl", "Shaders/ProvinceTessControl.glsl", "Shaders/ProvinceTessEval.glsl");
	mProgram[3]->Bind();
	mBuffer->Bind();
	mProgram[3]->setInt("prov", 9);
	mProgram[3]->setInt("terrain", 0);
	mProgram[3]->setInt("Countries", 2);
	mBuffer->UnBind();
	mProgram[3]->UnBind();
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
			mProgram[0]->Bind();
			mProgram[0]->setInt("currentDraw", 0);
			mProgram[0]->UnBind();
		}
		if (e->key.keysym.sym == SDLK_F2)
		{
			mProgram[0]->Bind();
			mProgram[0]->setInt("currentDraw", 1);
			mProgram[0]->UnBind();
		}
		if (e->key.keysym.sym == SDLK_F3)
		{
			mProgram[0]->Bind();
			mProgram[0]->setInt("currentDraw", 2);
			mProgram[0]->UnBind();
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


	mProgram[0] = std::make_unique<Shader>("Shaders/TerrainVertex.glsl", "Shaders/TerrainFragment.glsl", "Shaders/TerrainTessControl.glsl", "Shaders/TerrainTessEval.glsl");
	mProgram[0]->Bind();
	mBuffer = std::make_unique<BufferObject>();
	mBuffer->Set(Vertices.data(), TexCoord.data(), Indices.data(), GL_STATIC_DRAW, sizeof(glm::vec3) * Vertices.size(), sizeof(glm::vec2) * TexCoord.size(), sizeof(GLuint) * Indices.size());
	mTexture = std::make_unique<Texture>();



	mTexture->AddCache(
		glm::vec2(5632,2048),
		"Resources/cache/ht",
		GL_RGB, GL_TEXTURE0, Parameter::NONE, true, true,
		"Resources/terrain/ht.bmp");
	mProgram[0]->setInt("terrain", 0);

	mTexture->AddCache(
		glm::vec2(5632, 2048),
		"Resources/cache/countries",
		GL_RGB, GL_TEXTURE2,
		Parameter::LINEAR);
	mProgram[0]->setInt("Countries", 2);


	// TODO: Загружать текстуры автоматически из файла
	std::ifstream TextureConfig("Resources/texture.json");
	boost::property_tree::ptree pt;
	boost::property_tree::read_json(TextureConfig, pt);
	for (auto& array_element : pt)
	{
		mTextures.push_back(new TextureFormat());
		mTextures.back()->Name = array_element.first;
		mTextures.back()->ID = GL_TEXTURE0 + array_element.second.get<int>("ID");
		mTextures.back()->UniformID = array_element.second.get<int>("ID");
		mTextures.back()->Path = array_element.second.get<std::string>("Path");
		if (array_element.second.get<std::string>("Format") == "RGBA")
			mTextures.back()->Format = GL_RGBA;
		else
			mTextures.back()->Format = GL_RGB;
		if (array_element.second.get<std::string>("Parameter") == "LINEAR")
			mTextures.back()->Param = Parameter::LINEAR;
		else if(array_element.second.get<std::string>("Parameter") == "CTG")
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
	
	/*this->AsyncLoadTexture("Resources/terrain/bm1.png", "BlendMap1");
	this->AsyncLoadTexture("Resources/terrain/atlas0.bmp", "Atlas");
	this->AsyncLoadTexture("Resources/terrain/bm3.png", "BlendMap2");
	this->AsyncLoadTexture("Resources/terrain/8i1c3dnd28h51.png", "ProvBorder");
	this->AsyncLoadTexture("Resources/terrain/bm2.png", "BlendMap3");
	this->AsyncLoadTexture("Resources/terrain/World_normal.png", "WorldNormal");
	this->AsyncLoadTexture("Resources/terrain/atlas_normal0.bmp", "AtlasNormal");
	this->AsyncLoadTexture("Resources/terrain/provinces.bmp", "Provinces");
	this->AsyncLoadTexture("Resources/terrain/provinces.bmp", "ProvincesBlend");	*/


	this->textureLoadThreads.join_all();
	for (auto& thread : this->mThreads)
		this->textureLoadThreads.remove_thread(thread);


	for (auto& texture : mTextures)
	{
		mTexture->Add(
			texture->Size,
			mTextureDatas.at(texture->Name),
			texture->Format, texture->ID,
			texture->Param
		);
		mProgram[0]->setInt(texture->UniformName, texture->UniformID);
	}

	/*mTexture->Add(
		glm::vec2(5632,2048),
		mTextureDatas.at("BlendMap1"),
		GL_RGBA, GL_TEXTURE1,
		Parameter::LINEAR);
	mProgram[0]->setInt("terrain_map", 1); 

	mTexture->Add(
		glm::vec2(2048, 2048),
		mTextureDatas.at("Atlas"),
		GL_RGB, GL_TEXTURE3,
		Parameter::CTG);
	mProgram[0]->setInt("TerrainTextureID", 3); 

	mTexture->Add(
		glm::vec2(5632, 2048),
		mTextureDatas.at("BlendMap2"),
		GL_RGBA, GL_TEXTURE4,
		Parameter::LINEAR);
	mProgram[0]->setInt("bm3", 4);	

	mTexture->Add(
		glm::vec2(2816, 1024),
		mTextureDatas.at("ProvBorder"),
		GL_RGBA, GL_TEXTURE5,
		Parameter::LINEAR);
	mProgram[0]->setInt("province_border", 5);	

	mTexture->Add(
		glm::vec2(5632, 2048),
		mTextureDatas.at("BlendMap3"),
		GL_RGBA, GL_TEXTURE6,
		Parameter::LINEAR);
	mProgram[0]->setInt("terra", 6);	

	mTexture->Add(
		glm::vec2(5632, 2048),
		mTextureDatas.at("WorldNormal"),
		GL_RGBA, GL_TEXTURE7,
		Parameter::LINEAR);
	mProgram[0]->setInt("wn", 7);	

	mTexture->Add(
		glm::vec2(2048, 2048),
		mTextureDatas.at("AtlasNormal"),
		GL_RGB, GL_TEXTURE8,
		Parameter::LINEAR);
	mProgram[0]->setInt("an", 8);	

	mTexture->Add(
		glm::vec2(5632, 2048),
		mTextureDatas.at("Provinces"),
		GL_RGB, GL_TEXTURE9,
		Parameter::NEAREST_CTG);
	mProgram[0]->setInt("provinces", 9);	

	mTexture->Add(
		glm::vec2(5632, 2048),
		mTextureDatas.at("ProvincesBlend"),
		GL_RGB, GL_TEXTURE18,
		Parameter::LINEAR);
	mProgram[0]->setInt("provincesBlend", 18);	*/
	
	mBuffer->UnBind();
	mProgram[0]->UnBind();
}

void WorldRenderer::WaterInit()
{
	mProgram[1] = std::make_unique<Shader>(
		"Shaders/WaterVertex.glsl",
		"Shaders/WaterFragment.glsl",
		"Shaders/WaterTessControl.glsl",
		"Shaders/WaterTessEval.glsl");
	mProgram[1]->Bind();
	mBuffer->Bind();
	mProgram[1]->setFloat("speed", 0.14f);
	mProgram[1]->setFloat("amount", 990.000101f);
	mProgram[1]->setFloat("height", 0.001);

	/*mTexture->Add(
		"Resources/terrain/underwater_terrain_0.png",
		GL_RGBA,
		GL_TEXTURE10,
		Parameter::LINEAR
		);
	mProgram[1]->setInt("TexWater", 10);

	mTexture->Add(
		"Resources/terrain/matchingNormalMap.png",
		GL_RGBA,
		GL_TEXTURE11,
		Parameter::NONE
	);
	mProgram[1]->setInt("watnorm", 11);

	mTexture->Add(
		"Resources/terrain/waterDUDV.png",
		GL_RGBA,
		GL_TEXTURE12,
		Parameter::NONE
	);
	mProgram[1]->setInt("dudv", 12);

	mTexture->Add(
		"Resources/terrain/cm.png",
		GL_RGBA,
		GL_TEXTURE13,
		Parameter::LINEAR
	);
	mProgram[1]->setInt("cm", 13);

	mTexture->Add(
		"Resources/terrain/heightmap.bmp",
		GL_RGB,
		GL_TEXTURE14,
		Parameter::NEAREST_CTG
	);
	mProgram[1]->setInt("wterrain", 14);*/

	mTexture->LoadCubemap(
		{ "Resources/terrain/cubemap/right.jpg",
		"Resources/terrain/cubemap/left.jpg",
		"Resources/terrain/cubemap/up.jpg",
		"Resources/terrain/cubemap/down.jpg",
		"Resources/terrain/cubemap/front.jpg",
		"Resources/terrain/cubemap/back.jpg" },
		GL_TEXTURE15
	);
	mProgram[1]->setInt("skybox", 15);

	mBuffer->UnBind();

	mProgram[1]->UnBind();
}

void WorldRenderer::CloudsInit()
{
	mProgram[2] = std::make_unique<Shader>(
		"Shaders/CloudsVertex.glsl",
		"Shaders/CloudsFragment.glsl",
		"Shaders/CloudsTessControl.glsl",
		"Shaders/CloudsTessEval.glsl");
	mProgram[2]->Bind();
	mBuffer->Bind();

	/*mTexture->Add(
		"Resources/terrain/clouds.png",
		GL_RGBA,
		GL_TEXTURE16,
		Parameter::LINEAR
	);
	mProgram[2]->setInt("clouds", 16);*/

	mBuffer->UnBind();
	mProgram[2]->UnBind();
}

void WorldRenderer::AsyncLoadTexture(std::string Path, std::string TextureName)
{
	mThreads.push_back(new boost::thread([this](std::string path, std::string name)
	{
		//boost::lock_guard<boost::mutex> lg{mThreadMutex};
		mTextureDatas.emplace(name, stbi_load(path.c_str(), &mTextureX, &mTextureY, &mTextureChanel, 0));
	}, Path, TextureName));
	textureLoadThreads.add_thread(mThreads.back());
}
