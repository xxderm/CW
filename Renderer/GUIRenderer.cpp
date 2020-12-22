#include "GUIRenderer.h"

GUIRenderer::GUIRenderer(std::string uiPath, int fontSize, Scene* scene)
	: mUiPath(uiPath), mFontSize(fontSize), mScene_ptr(scene)
{
	if (!scene)
		LOG(WARNING) << "GUIRenderer: Scene is nullptr";
}

void GUIRenderer::Render()
{		
	for (auto& gui : mGuis->getGui())
	{
		if (gui.second->Visible)
		{
			mProgram->Bind();
			mProgram->setMat4("transformationMatrix",
				CreateTransformationMatrix(gui.second->Position, gui.second->Scale));
			mProgram->setInt("guiTexture", gui.second->TextureId);
			mProgram->setVec4("guiColor", gui.second->Color);
			if (gui.second->TextureId == -1)
				mProgram->setBool("TextureMode", 0);
			else
				mProgram->setBool("TextureMode", 1);
			mQuad->Draw(GL_TRIANGLE_STRIP, 8);
			mProgram->UnBind();	

			glDisable(GL_DEPTH_TEST);
			for (auto& text : gui.second->Text)
			{
				float x = (mWinX * text.second.Position.x) / 100;
				float y = (mWinY * text.second.Position.y) / 100;
				mText.RenderText(
					text.second.Text,
					x,
					y,
					text.second.Scale,
					glm::vec4(text.second.Color));
			}
			glEnable(GL_DEPTH_TEST);
		}
	}
}

void GUIRenderer::Init(SDL_Window* wnd)
{
	mProgram = std::make_unique<Shader>("Shaders/GUIVertex.glsl", "Shaders/GUIFragment.glsl");
	mProgram->Bind();
	mQuad = std::make_unique<BufferObject>();
	float Vertices[] = { -1, 1, -1, -1, 1, 1, 1, -1 };
	int Indices[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	mQuad->Set(Vertices, nullptr, Indices, GL_STATIC_DRAW, 4 * 8, 0, 4 * 8, 2);
	mQuad->UnBind();
	mProgram->UnBind();

	mGuis = std::make_unique<GUITexture>();

	
	SDL_GetWindowSize(wnd, &mWinX, &mWinY);
	mText.Init("Resources/font/17541.ttf", glm::vec2(mWinX, mWinY), this->mFontSize);
	Reader::getInstance()->getUI(mGuis.get(), mUiPath);


	mCommand.emplace("Exit", new ExitCommand(mScene_ptr));
	mCommand.emplace("Start", new ChangeSceneCommand(mScene_ptr, CountrySelectScene::getInstance()));
	mCommand.emplace("GetLobbies", new GetLobbyListCommand(mScene_ptr->getPacket(), mScene_ptr->getSocket()));
	mCommand.emplace("ClearLobbies", new ClearLobbyListCommand(&mLobbies));
}

void GUIRenderer::Update()
{
	this->Listen();
	//Reader::getInstance()->getUI(mGuis.get(), mUiPath);
}

void GUIRenderer::setCamera(Camera* camera)
{
}

void GUIRenderer::setMousePicker(MousePicker* mp)
{
}

void GUIRenderer::HandleEvent(SDL_Event* e, SDL_Window* wnd)
{
	//Reader::getInstance()->getUI(mGuis.get(), mUiPath);

	SDL_GetMouseState(&mMouseX, &mMouseY);
	if (e->type == SDL_KEYDOWN)
	{
		try
		{
			for (auto& gui : this->mGuis->getGui())
			{
				if (gui.second->Type == "Input")
				{
						if ((e->key.keysym.sym != SDLK_LSHIFT && e->key.keysym.sym != SDLK_LALT && e->key.keysym.sym != SDLK_BACKQUOTE) && gui.second->Active)
						{
							// erase last sym
							if (e->key.keysym.sym == SDLK_BACKSPACE && mGuis->Get(gui.first)->Text.at("Input").Text.size() > 0)
								mGuis->Get(gui.first)->Text.at("Input").Text
								.erase(mGuis->Get(gui.first)->Text.at("Input").Text.end() - 1);
							// add sym
							else
								mGuis->Get(gui.first)->Text.at("Input").Text += e->key.keysym.sym;
						}
						if (e->key.keysym.sym == int(char(gui.second->Key.second)) && gui.second->Key.first)
						{		
							gui.second->Visible = !gui.second->Visible;
							mGuis->SetVisible(gui.second->For, !mGuis->Get(gui.second->For)->Visible);
							gui.second->Text.at("Input").Text.clear();
						}
				}
				else if (e->key.keysym.sym == int(char(gui.second->Key.second)) && gui.second->Key.first)
				{
					if(mGuis->isAllInputHidden())
						gui.second->Visible = !gui.second->Visible;
				}
			}
		}
		catch (std::exception& ex)
		{
			LOG(ERROR) << ex.what();
		}
	}

	for (auto& gui : this->mGuis->getGui())
	{			
		if (gui.second->Visible)
		{		
			if (gui.second->DynamicText)
			{
				if (mScene_ptr->getUser()->getCountry())
				{
					gui.second->Text.count("CountryName") > 0 ?
						gui.second->Text.at("CountryName").Text =
							mScene_ptr->getUser()->getCountry()->Name.at(mScene_ptr->getUser()->getCountry()->RulingParty)
						:
						0;
					gui.second->Text.count("PartyName") > 0 ?
						gui.second->Text.at("PartyName").Text =
						mScene_ptr->getUser()->getCountry()->PartyName
						:
						0;
					gui.second->Text.count("PresidentName") > 0 ?
						gui.second->Text.at("PresidentName").Text =
						mScene_ptr->getUser()->getCountry()->LeaderName
						:
						0;

				}

			}
			if (gui.second->LobbyIndex != -1)
			{
				if (mLobbies.size() >= gui.second->LobbyIndex)
				{
					gui.second->Visible = true;
					std::string IndexT = "L" + std::to_string(gui.second->LobbyIndex) + "T";
					std::string IndexV = "L" + std::to_string(gui.second->LobbyIndex) + "V";
					std::string IndexC = "L" + std::to_string(gui.second->LobbyIndex) + "C";
					gui.second->Text
						.at(IndexT)
						.Text = std::to_string(gui.second->LobbyIndex) + " " + mLobbies.at(gui.second->LobbyIndex - 1).Name;
					gui.second->Text
						.at(IndexV)
						.Text = mLobbies.at(gui.second->LobbyIndex - 1).Version;
					gui.second->Text
						.at(IndexC)
						.Text = std::to_string(mLobbies.at(gui.second->LobbyIndex - 1).Clients) + "/" + std::to_string(32);
				}
			}
			if (gui.second->isHovered(MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY))))
			{
				mGuis->SetColor(gui.first, gui.second->hoverColor);
				if (e->type == SDL_MOUSEBUTTONDOWN)
				{
					if (!gui.second->CommandOnClick.first.empty())
					{
						mCommand.at(gui.second->CommandOnClick.first)->Execute();
					}
					if (!gui.second->ShowToClick.empty())
					{
						for (auto& form : gui.second->ShowToClick)
						{
							mGuis->getGui().at(form)->Visible = true;
						}
					}
					if (!gui.second->HideToClick.empty())
					{
						for (auto& form : gui.second->HideToClick)
						{
							mGuis->getGui().at(form)->Visible = false;
						}
					}
					gui.second->Active = !gui.second->Active;
				}
			}
			else
			{
				if (e->type == SDL_MOUSEBUTTONDOWN)
				{
					gui.second->Active = false;
				}
				mGuis->SetColor(gui.first, gui.second->baseColor);
			}
			(gui.second->ActiveHighlight && gui.second->Active) ? gui.second->Color *= gui.second->ActiveHighlightIntensity : gui.second->Color;
			
		}		
	}
}

glm::mat4 GUIRenderer::CreateTransformationMatrix(glm::vec2 translation, glm::vec2 scale)
{
	glm::mat4 matrix =
		glm::identity<glm::mat4>();
	matrix *= glm::translate(glm::vec3(translation.x, translation.y, 0));
	matrix *= glm::scale(glm::vec3(scale.x, scale.y, 1.f));
	return matrix;
}

void GUIRenderer::Listen()
{
	if (SDLNet_UDP_Recv(*mScene_ptr->getSocket(), mScene_ptr->getPacket()))
	{
		//std::cout << "Got: " << scene->getPacket()->data << std::endl;
		if (mScene_ptr->getPacket()->data[0] == (Uint8)'5')
		{
			std::string message = std::string((char*)mScene_ptr->getPacket()->data);

			bool state = false;
			std::string line;
			mLobbies.clear();

			for (auto& i : message)
			{				
				if (i == '|' && state)
				{
					auto lobby = Reader::getInstance()->split(line, " ");
					Lobby curr;
					curr.Name = lobby[0];
					curr.Capacity = std::stoi(lobby[1]);
					curr.Version = lobby[2];
					curr.Clients = std::stoi(lobby[3]);
					mLobbies.push_back(curr);
					state = false;
					line.clear();
				}	
				else if (i == '|')
				{
					state = !state;
				}
				if (state && i != '|')
				{
					line += i;
				}
			}

		}
	}
}
