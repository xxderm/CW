#include "GUIRenderer.h"

GUIRenderer::GUIRenderer(std::string uiPath, int fontSize, Scene* scene, World* world)
	: mUiPath(uiPath), mFontSize(fontSize), mScene_ptr(scene), mWorld_ptr(world)
{
	if (!scene)
		LOG(WARNING) << "GUIRenderer: Scene is nullptr";
}

void GUIRenderer::Render()
{		
	for (auto& gui : mGuis->getGui())
	{
	

		// ������������� ������ � ������������ ���������
		if (!gui.second->Parent.empty() )
		{
			auto parent = mGuis->Get(gui.second->Parent);;
			auto xPos = parent->Position.x;
			auto yPos = ( (parent->Position.y + parent->Scale.y) - gui.second->Scale.y) + gui.second->ScrollPosition.y;

			
			gui.second->Position = glm::vec2(
				xPos + gui.second->Padding.x,
				yPos - gui.second->Padding.y);
			
			// ������� ��������� �� ������������� ��������
			gui.second->Visible = mGuis->Get(gui.second->Parent)->Visible;
		}

		if (gui.second->Visible)
		{
			// ������������ ������� ��� ���������
			if (gui.second->Scroll)
			{
				ApplyScissors(gui.second->Parent);
			}
			// ���� ������������ ������� ����� �������
			if (!gui.second->Parent.empty())
			{
				if (mGuis->Get(gui.second->Parent)->Scroll)
				{
					auto parent = mGuis->Get(gui.second->Parent);
					ApplyScissors(parent->Parent);
				}
			}

			// ������ �����
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

		
			// ������ ������ �����
			glDisable(GL_DEPTH_TEST);
			for (auto& text : gui.second->Text)
			{
				auto guiWndCoords = glm::vec2(
					gui.second->Position.x - gui.second->Scale.x,
					gui.second->Position.y + gui.second->Scale.y);

				auto normPos = text.second.Position;

				auto x = (guiWndCoords.x + 0.01) + normPos.x;
				auto y = (guiWndCoords.y - 0.0175) - normPos.y;

				auto pos = MousePicker::NormalizedDevCoordsToWindowsCoords(x, y, glm::vec2(mWinX, mWinY));
				

				int PosX = mText.RenderText(
						text.second.Text,
					pos.x,
					pos.y,
						text.second.Scale,
						glm::vec4(text.second.Color));

				auto normCoords = MousePicker::getNormalizedDeviceCoords(PosX, y, glm::vec2(mWinX, mWinY));
				if (normCoords.x >= gui.second->Position.x + gui.second->Scale.x)
					text.second.Scale -= 0.05;
				if (normCoords.x + 0.05 < gui.second->Position.x + gui.second->Scale.x && text.second.Scale < text.second.BaseScale)
					text.second.Scale = text.second.BaseScale;

			}
			glEnable(GL_DEPTH_TEST);	

			// ��������� ���� �� ������� ��� ������� ����������� ��������� �����
			if (!gui.second->Parent.empty())
				if(mGuis->Get(gui.second->Parent)->Scroll)
					glDisable(GL_SCISSOR_TEST);
			if (gui.second->Scroll)
				glDisable(GL_SCISSOR_TEST);
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
	
	GuiFormat* slider = new GuiFormat();
	slider->Padding = glm::vec2(0.18, 0.0);
	slider->Color = glm::vec4(0, 0, 1, 1);
	slider->baseColor = slider->Color;
	slider->hoverColor = slider->Color;
	slider->Visible = 1;
	slider->Name = "Slider";
	slider->Scale = glm::vec2(0.02, 0.04);
	slider->Type = "Scroll";
	slider->For = "TestG1";
	slider->Parent = "parent";

	GuiFormat* parent = new GuiFormat();
	parent->Name = "parent";
	parent->Color = glm::vec4(0.5);
	parent->baseColor = parent->Color;
	parent->hoverColor = parent->Color;
	parent->Visible = 1;
	parent->Position = glm::vec2(-0.5, 0.0);
	parent->Scale = glm::vec2(0.2, 0.4);

	GuiFormat* format = new GuiFormat();
	format->Name = "TestG1";
	format->Color = glm::vec4(1);
	format->baseColor = format->Color;
	format->hoverColor = format->Color;
	format->Visible = 1;
	format->Position = glm::vec2(0.0, 0.0);
	format->Padding = format->Position;
	format->Scale = glm::vec2(0.2, 3);
	format->Scroll = 1;
	format->Parent = "parent";
	Str tmp;
	tmp.Scale = 1;
	tmp.BaseScale = 1;
	tmp.Color = glm::vec4(1, 0, 1, 1);
	tmp.Text = "Test";
	tmp.Position = glm::vec2(0.0, 0.126);
	format->Text.emplace("Test", tmp);
	for (size_t i = 0; i < 40; i++)
	{
		tmp.Position.y += 0.086;
		format->Text.emplace("Test" + std::to_string(i), tmp);
	}
	for (size_t i = 0; i < 15; i++)
	{
		GuiFormat* element = new GuiFormat();
		element->Name = "Element" + std::to_string(i);
		element->Color = glm::vec4(0.3);
		element->baseColor = element->Color;
		element->hoverColor = glm::vec4(0.5);
		element->Visible = 1;
		element->Padding = glm::vec2(0.002, 0.1 + (i) );
		element->Scale = glm::vec2(0.15, 0.1);
		element->Parent = "TestG1";
		mGuis->Add(element->Name, element);
	}
	mGuis->Add("Slider", slider);
	mGuis->Add("TestG1", format);
	mGuis->Add("parent", parent);

	// ��������
	mCommand.emplace("Exit", new ExitCommand(mScene_ptr));
	mCommand.emplace("Start", new ChangeSceneCommand(mScene_ptr, CountrySelectScene::getInstance()));
	mCommand.emplace("GetLobbies", new GetLobbyListCommand(mScene_ptr->getPacket(), mScene_ptr->getSocket()));
	mCommand.emplace("ClearLobbies", new ClearLobbyListCommand(&mLobbies));
	mCommand.emplace("SelectCountry", new SelectCountryCommand(mScene_ptr, &mCountry_ptr));
	mCommand.emplace("AddForm", new AddFormCommand(mGuis.get()));
	mCommand.emplace("GetForm", new GetFormCommand(mGuis.get(), &mFormNameTarget_ptr));
	mCommand.emplace("SaveForm", new SaveFormCommand(mGuis.get(), &mGuiPathTarget_ptr));
	mCommand.emplace("ApplyForm", new ApplyFormSettingsCommand(mGuis.get(), &mFormNameTarget_ptr));
}

void GUIRenderer::Update()
{
	this->Listen();
	//Reader::getInstance()->getUI(mGuis.get(), mUiPath, true);



	SDL_GetMouseState(&mMouseX, &mMouseY);

	for (auto& gui : mGuis->getGui())
	{			
		if (gui.second->Moveable &&
			(				
				gui.second->Active &&
				gui.second->isHovered(MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY)))								
			) &&
			mMouseButtonPressed)
		{
			// �������� �����
			auto mouse = MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY));			
			auto center = gui.second->Position;
			// ���� ��������� ��������, �� ���������� ��
			if (mFormDistanceDifference.x == -2)
				mFormDistanceDifference = center - mouse;
			auto result = mouse + mFormDistanceDifference;		

			if (gui.second->Parent.empty())
				gui.second->Position = result;
			else
			{				
				// �������� ��������� ��������
				auto parentPos = mGuis->Get(gui.second->Parent)->Position;
				gui.second->Padding.x = mouse.x - parentPos.x;
				gui.second->Padding.y = ((-mouse.y) - (parentPos.y)) + 0.0;
			}
		}		
		if (mScene_ptr->getUser()->getStatus() == UserState::DEBUGGING)
		{
			// �������� �������� ����� � ������ �������
			if (
				(!gui.second->DebugElement || mScene_ptr->getEvent()->key.keysym.sym == SDLK_LCTRL) &&
				(mMouseButtonPressed && gui.second->Active))
			{
				mFormNameTarget_ptr = gui.first;
				mCommand.at("GetForm")->Execute();
			}			
		}	
		if (gui.second->Type == "Scroll")
		{
			// ���� ������ ������, �� ����������� �����
			if (
				gui.second->isHovered(MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY))) &&
				mMouseButtonPressed
				)
			{
				auto parent = mGuis->Get(gui.second->Parent);
				auto minPosY = parent->Position.y + (parent->Scale.y);
				auto maxPosY = parent->Position.y - (parent->Scale.y);
				auto currentScrollPos = MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY)).y;									
				auto different = (minPosY) - (currentScrollPos);				
				gui.second->Padding.y = different - 0.04;

				auto sliderScale = gui.second->Scale.y * 2;
				auto sliderPosMin = (gui.second->Padding.y);
				auto sliderPosMax = gui.second->Padding.y + (sliderScale);
				auto maxPoint = parent->Scale.y * 2;

				if (sliderPosMin < 0.0)
					gui.second->Padding.y = 0.0;
				if (sliderPosMax > maxPoint)
					gui.second->Padding.y = maxPoint - sliderScale;

				auto content = mGuis->Get(gui.second->For);
				auto slidePercent = (gui.second->Padding.y) / maxPoint;
				auto contentMaxPoint = (content->Scale.y * 2);
				auto contentPos = contentMaxPoint * slidePercent;
				if (contentPos + sliderScale > contentMaxPoint)
					contentPos = contentMaxPoint;
				content->ScrollPosition.y = contentPos;
			}
		}
	}
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
	//SDL_GetMouseState(&mMouseX, &mMouseY);


	if (e->type == SDL_MOUSEBUTTONDOWN)
		mMouseButtonPressed = true;
	// ���� ������ ���� �������, �� �������� ������� � ��������� �� ������ �����
	if (e->type == SDL_MOUSEBUTTONUP)
	{
		mMouseButtonPressed = false;
		mFormDistanceDifference = glm::vec2(-2);
	}
	if (e->type == SDL_KEYUP)
	{
		if (e->key.keysym.sym == SDLK_LSHIFT)
			mShiftIsPressed = false;
	}
	if (e->type == SDL_KEYDOWN)
	{
		if (e->key.keysym.sym == SDLK_LSHIFT)
			mShiftIsPressed = true;

		// �������� �����
		if (e->key.keysym.sym == SDLK_F1)
		{
			mGuis->Clear();
			mGuis->getGui().clear();	
			Reader::getInstance()->getUI(mGuis.get(), mUiPath, true);
		}

		try
		{
			for (auto& gui : this->mGuis->getGui())
			{		
				// ��������� ���� �����
				if (gui.second->Type == "Input")
				{
					if ((e->key.keysym.sym != SDLK_LSHIFT && e->key.keysym.sym != SDLK_LALT && e->key.keysym.sym != SDLK_BACKQUOTE) && gui.second->Active)
					{
						// ������� ��������� ������
						if (e->key.keysym.sym == SDLK_BACKSPACE && mGuis->Get(gui.first)->Text.at("Input").Text.size() > 0)
							mGuis->Get(gui.first)->Text.at("Input").Text
							.erase(mGuis->Get(gui.first)->Text.at("Input").Text.end() - 1);
						// �������� ������
						else if (mShiftIsPressed)
						{
							mGuis->Get(gui.first)->Text.at("Input").Text += std::toupper(e->key.keysym.sym);
						}
						else
						{							
							mGuis->Get(gui.first)->Text.at("Input").Text += e->key.keysym.sym;
						}
					}				
					// ����������� ��������� ����� ��� ������� �� ������� ������� 
					if (e->key.keysym.sym == int(char(gui.second->Key.second)) && gui.second->Key.first)
					{		
						gui.second->Visible = !gui.second->Visible;
						mGuis->SetVisible(gui.second->For, !mGuis->Get(gui.second->For)->Visible);
						gui.second->Text.at("Input").Text.clear();
					}
				}
				// ����������� ��������� ��� ������ ����� ��� ������� �� ������� �������
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
			// ����������� ��������� ����
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

			// ���������� ������ �����
			if (gui.second->LobbyIndex != -1)
			{
				std::string IndexT = "L" + std::to_string(gui.second->LobbyIndex) + "T";
				std::string IndexV = "L" + std::to_string(gui.second->LobbyIndex) + "V";
				std::string IndexC = "L" + std::to_string(gui.second->LobbyIndex) + "C";
				if (mLobbies.size() >= gui.second->LobbyIndex)
				{
					gui.second->Visible = true;
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
				else
				{
					gui.second->Text
						.at(IndexT)
						.Text.clear();
					gui.second->Text
						.at(IndexV)
						.Text.clear();
					gui.second->Text
						.at(IndexC)
						.Text.clear();
				}
			}


			if (gui.second->isHovered(MousePicker::getNormalizedDeviceCoords(mMouseX, mMouseY, glm::vec2(mWinX, mWinY))))
			{
				mGuis->SetColor(gui.first, gui.second->hoverColor);
				if (e->type == SDL_MOUSEBUTTONDOWN)
				{							
					// ���������� ��������� ������
					if (!gui.second->SelectedCountryTag.empty())
					{
						mCountry_ptr = *mWorld_ptr->getCountries()->getCountryByTag(gui.second->SelectedCountryTag);
					}

					// �������� ����������
					if (!gui.second->CommandOnClick.first.empty())
					{
						if (gui.second->CommandOnClick.first == "GetForm")						
							mFormNameTarget_ptr = mGuis->Get("FormFindNameInput")->Text.at("Input").Text;
						if(gui.second->CommandOnClick.first == "SaveForm")
							mGuiPathTarget_ptr = mGuis->Get("SaveUIInput")->Text.at("Input").Text;

						mCommand.at(gui.second->CommandOnClick.first)->Execute();
					}

					// ��������� �������� �� �������
					if (!gui.second->ShowToClick.empty())
					{
						for (auto& form : gui.second->ShowToClick)
						{
							mGuis->Get(form)->Visible = true;
						}
					}

					// ��������� �������� �� �������
					if (!gui.second->HideToClick.empty())
					{
						for (auto& form : gui.second->HideToClick)
						{
							mGuis->Get(form)->Visible = false;


						}
					}
					
					// ��� ������� �� ����� ������������� ���������� �����
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

void GUIRenderer::ApplyScissors(std::string parentElementName)
{
	glEnable(GL_SCISSOR_TEST);


	auto parentPos = mGuis->Get(parentElementName)->Position;
	auto parentScale = mGuis->Get(parentElementName)->Scale;


	auto sciPos = MousePicker::NormalizedDevCoordsToWindowsCoords(parentPos.x, parentPos.y, glm::vec2(mWinX, mWinY));
	auto sciSize = MousePicker::NormalizedDevCoordsToWindowsCoords(parentScale.x, parentScale.y - (1.0 - parentScale.y), glm::vec2(mWinX, mWinY));

	glScissor(sciPos.x - (sciSize.x / 2), sciPos.y - (sciSize.y / 2) + 4, sciSize.x, sciSize.y - 4);
}

void GUIRenderer::Listen()
{
	if (SDLNet_UDP_Recv(*mScene_ptr->getSocket(), mScene_ptr->getPacket()))
	{
		//std::cout << "Got: " << scene->getPacket()->data << std::endl;
		std::stringstream jsonEncodedData((char*)mScene_ptr->getPacket()->data);
		boost::property_tree::ptree response;
		boost::property_tree::read_json(jsonEncodedData, response);
		if (response.get<int>("Signal") == SIGNAL::GET_LOBBY_LIST)
		{			
			mLobbies.clear();
			for (auto& lobby : response)
			{
				if (lobby.second.count("Name") == 0)
					mLobbies.clear();
				if (lobby.first == "Signal")
					continue;
				Lobby currentLobby;
				currentLobby.Name = lobby.second.get<std::string>("Name");
				currentLobby.Capacity = lobby.second.get<int>("Capacity");
				currentLobby.Version = lobby.second.get<std::string>("Version");
				currentLobby.Clients = lobby.second.get<int>("Clients");
				mLobbies.push_back(currentLobby);
			}
		}
	}
}
