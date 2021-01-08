#include "UICommand.h"

ExitCommand::ExitCommand(Scene* scene)
	: mScene_ptr(scene)
{
}

void ExitCommand::Execute()
{
	mScene_ptr->Exit();
}

ChangeSceneCommand::ChangeSceneCommand(Scene* src, SceneMachine* dst)
	: mScene_ptr(src), mSceneMachine_ptr(dst)
{
}

void ChangeSceneCommand::Execute()
{
	mScene_ptr->ChangeScene(mSceneMachine_ptr);
}

ClearLobbyListCommand::ClearLobbyListCommand(std::vector<Lobby>* lobbies)
	: mLobbies(lobbies)
{

}

void ClearLobbyListCommand::Execute()
{
	mLobbies->clear();
}

SelectCountryCommand::SelectCountryCommand(Scene* scene, CountryFormat* country)
	: mScene_ptr(scene), mCountry_ptr(country)
{
}

void SelectCountryCommand::Execute()
{
	if(mScene_ptr->getUser()->getStatus() == UserState::COUNTRY_SELECT)
		mScene_ptr->getUser()->setCountry(mCountry_ptr);
}

AddFormCommand::AddFormCommand(GUITexture* Gui_ptr)
	: mGui_ptr(Gui_ptr)
{
}

void AddFormCommand::Execute()
{
	GuiFormat* format = new GuiFormat();
	format->Name = "element" + std::to_string(mGui_ptr->getGui().size());
	format->Visible = true;
	format->Moveable = true;
	format->TextureId = -1;
	format->Position = glm::vec2(0.0, 0.0);
	format->Color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	format->hoverColor = format->Color;
	format->Scale = glm::vec2(0.3, 0.6);
	mGui_ptr->Add(format->Name, format, true);
}

GetFormCommand::GetFormCommand(GUITexture* Gui_ptr, std::string* FormName)
	: mGui_ptr(Gui_ptr), mFormName_ptr(FormName)
{
}

void GetFormCommand::Execute()
{
	if (!mGui_ptr->Get(*mFormName_ptr))
		LOG(ERROR) << "GUI element not fount.";
	else
	{
		mGui_ptr->Get("FormNameInput")->Text.at("Input").Text =
			mGui_ptr->Get(*mFormName_ptr)->Name;

		mGui_ptr->Get("FormTextureInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->TextureId);

		mGui_ptr->Get("FormScaleInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Scale.x) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Scale.y);
		mGui_ptr->Get("FormPosInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Position.x) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Position.y);
		mGui_ptr->Get("FormColorInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Color.r) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Color.g) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Color.b) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Color.a);
		mGui_ptr->Get("FormHoverInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->hoverColor.r) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->hoverColor.g) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->hoverColor.b) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->hoverColor.a);
		mGui_ptr->Get("FormMoveableInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Moveable);
		mGui_ptr->Get("FormParentInput")->Text.at("Input").Text =
			mGui_ptr->Get(*mFormName_ptr)->Parent;
		mGui_ptr->Get("FormTypeInput")->Text.at("Input").Text =
			mGui_ptr->Get(*mFormName_ptr)->Type;
		mGui_ptr->Get("FormForInput")->Text.at("Input").Text =
			mGui_ptr->Get(*mFormName_ptr)->For;
		mGui_ptr->Get("FormVisibleInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Visible);

		for (auto& element : mGui_ptr->Get(*mFormName_ptr)->ShowToClick)
		{
			mGui_ptr->Get("FormShowInput")->Text.at("Input").Text = element;
			if (element != mGui_ptr->Get(*mFormName_ptr)->ShowToClick.back())
				mGui_ptr->Get("FormShowInput")->Text.at("Input").Text += " ";
		}

		
		for (auto& element : mGui_ptr->Get(*mFormName_ptr)->HideToClick)
		{
			mGui_ptr->Get("FormHideInput")->Text.at("Input").Text = element;

			if (element != mGui_ptr->Get(*mFormName_ptr)->HideToClick.back())
				mGui_ptr->Get("FormShowInput")->Text.at("Input").Text += " ";
		}

		mGui_ptr->Get("FormHotKeyInput")->Text.at("Input").Text =
			(char)mGui_ptr->Get(*mFormName_ptr)->Key.second;

		mGui_ptr->Get("FormCommandInput")->Text.at("Input").Text =
			mGui_ptr->Get(*mFormName_ptr)->CommandOnClick.first;

		mGui_ptr->Get("FormActHighInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->ActiveHighlight);

		mGui_ptr->Get("FormActIntenInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->ActiveHighlightIntensity);

		mGui_ptr->Get("FormPaddingInput")->Text.at("Input").Text =
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Padding.x) + " " +
			std::to_string(mGui_ptr->Get(*mFormName_ptr)->Padding.y);
	}
}

SaveFormCommand::SaveFormCommand(GUITexture* Gui_ptr, std::string* GuiSavePath)
	: mGui_ptr(Gui_ptr), mGuiSavePath(GuiSavePath)
{
}

void SaveFormCommand::Execute()
{
	boost::property_tree::ptree pt;
	boost::property_tree::ptree child;
	boost::property_tree::ptree children;
	for (auto& element : mGui_ptr->getGui())
	{
		if (element.second->DebugElement)
			continue;
		pt.put(element.second->Name + ".Texture", element.second->TextureId);
		pt.put(element.second->Name + ".CenterPoint.x", element.second->Position.x);
		pt.put(element.second->Name + ".CenterPoint.y", element.second->Position.y);
		pt.put(element.second->Name + ".Scale.x", element.second->Scale.x);
		pt.put(element.second->Name + ".Scale.y", element.second->Scale.y);

		pt.put(element.second->Name + ".Padding.x", element.second->Padding.x);
		pt.put(element.second->Name + ".Padding.y", element.second->Padding.y);

		pt.put(element.second->Name + ".DebugElement", element.second->DebugElement);
		pt.put(element.second->Name + ".Scroll", element.second->Scroll);

		for (auto& text : element.second->Text)
		{
			pt.put(element.second->Name + ".Text." + text.first + ".String", text.second.Text);
			pt.put(element.second->Name + ".Text." + text.first + ".Location.x", text.second.Position.x);
			pt.put(element.second->Name + ".Text." + text.first + ".Location.y", text.second.Position.y);
			pt.put(element.second->Name + ".Text." + text.first + ".Color.r", text.second.Color.r);
			pt.put(element.second->Name + ".Text." + text.first + ".Color.g", text.second.Color.g);
			pt.put(element.second->Name + ".Text." + text.first + ".Color.b", text.second.Color.b);
			pt.put(element.second->Name + ".Text." + text.first + ".Color.a", text.second.Color.a);
			pt.put(element.second->Name + ".Text." + text.first + ".Name", text.first);
			pt.put(element.second->Name + ".Text." + text.first + ".Scale", text.second.Scale);
		}
		pt.put(element.second->Name + ".Color.r", element.second->baseColor.r);
		pt.put(element.second->Name + ".Color.g", element.second->baseColor.g);
		pt.put(element.second->Name + ".Color.b", element.second->baseColor.b);
		pt.put(element.second->Name + ".Color.a", element.second->baseColor.a);
		pt.put(element.second->Name + ".Hover.r", element.second->hoverColor.r);
		pt.put(element.second->Name + ".Hover.g", element.second->hoverColor.g);
		pt.put(element.second->Name + ".Hover.b", element.second->hoverColor.b);
		pt.put(element.second->Name + ".Hover.a", element.second->hoverColor.a);
		pt.put(element.second->Name + ".Visible", element.second->Visible);
		pt.put(element.second->Name + ".Type", element.second->Type);
		pt.put(element.second->Name + ".For", element.second->For);
		pt.put(element.second->Name + ".CommandOnClick", element.second->CommandOnClick.first);
		
		if (!element.second->ShowToClick.empty())
		{
			children.clear();
			for (auto& name : element.second->ShowToClick)
			{
				child.clear();
				child.put("", name);
				children.push_back({"", child});
			}

			pt.add_child(element.second->Name + ".ShowOnClickEvent", children);
		}
		if (!element.second->HideToClick.empty())
		{
			children.clear();
			for (auto& name : element.second->HideToClick)
			{
				child.clear();
				child.put("", name);
				children.push_back({ "", child });
			}
			pt.add_child(element.second->Name + ".HideOnClickEvent", children);
		}

		if(element.second->Key.first)
			pt.put(element.second->Name + ".Key", (char)element.second->Key.second);	

		pt.put(element.second->Name + ".Highlight", element.second->ActiveHighlight);
		pt.put(element.second->Name + ".HighlightIntensity", element.second->ActiveHighlightIntensity);
		
		if(element.second->LobbyIndex != -1)
			pt.put(element.second->Name + ".Lobby", element.second->LobbyIndex);

		pt.put(element.second->Name + ".Dynamic", element.second->DynamicText);

		if(!element.second->SelectedCountryTag.empty())
			pt.put(element.second->Name + ".StaticCountryTag", element.second->SelectedCountryTag);

		pt.put(element.second->Name + ".Moveable", element.second->Moveable);
		pt.put(element.second->Name + ".Parent", element.second->Parent);
	}

	std::stringstream ss;
	boost::property_tree::json_parser::write_json(ss, pt);
	std::ofstream save(*this->mGuiSavePath + ".json", std::ios::app);


	


	save << ss.str();
	save.close();
}

ApplyFormSettingsCommand::ApplyFormSettingsCommand(GUITexture* Gui_ptr, std::string* FormName)
	: mGui_ptr(Gui_ptr), mFormName_ptr(FormName)
{
}

void ApplyFormSettingsCommand::Execute()
{	 
	mGui_ptr->Get(*mFormName_ptr)->Name = mGui_ptr->Get("FormNameInput")->Text.at("Input").Text;

	mGui_ptr->Get(*mFormName_ptr)->TextureId = std::stoi(mGui_ptr->Get("FormTextureInput")->Text.at("Input").Text);

	auto Scale = Reader::getInstance()->split(mGui_ptr->Get("FormScaleInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->Scale.x = std::stof(Scale[0]);
	mGui_ptr->Get(*mFormName_ptr)->Scale.y = std::stof(Scale[1]);

	auto Position = Reader::getInstance()->split(mGui_ptr->Get("FormPosInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->Position.x = std::stof(Position[0]);
	mGui_ptr->Get(*mFormName_ptr)->Position.y = std::stof(Position[1]);


	auto Color = Reader::getInstance()->split(mGui_ptr->Get("FormColorInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->Color.r = std::stof(Color[0]);
	mGui_ptr->Get(*mFormName_ptr)->Color.g = std::stof(Color[1]);
	mGui_ptr->Get(*mFormName_ptr)->Color.b = std::stof(Color[2]);
	mGui_ptr->Get(*mFormName_ptr)->Color.a = std::stof(Color[3]);
	mGui_ptr->Get(*mFormName_ptr)->baseColor = mGui_ptr->Get(*mFormName_ptr)->Color;


	auto Hover = Reader::getInstance()->split(mGui_ptr->Get("FormHoverInput")->Text.at("Input").Text, " ");
	
	mGui_ptr->Get(*mFormName_ptr)->hoverColor.r = std::stof(Hover[0]);
	mGui_ptr->Get(*mFormName_ptr)->hoverColor.g = std::stof(Hover[1]);
	mGui_ptr->Get(*mFormName_ptr)->hoverColor.b = std::stof(Hover[2]);
	mGui_ptr->Get(*mFormName_ptr)->hoverColor.a = std::stof(Hover[3]);



	mGui_ptr->Get(*mFormName_ptr)->Moveable = std::stoi(mGui_ptr->Get("FormMoveableInput")->Text.at("Input").Text);

	mGui_ptr->Get(*mFormName_ptr)->Parent = mGui_ptr->Get("FormParentInput")->Text.at("Input").Text;
	mGui_ptr->Get(*mFormName_ptr)->Type = mGui_ptr->Get("FormTypeInput")->Text.at("Input").Text;
	mGui_ptr->Get(*mFormName_ptr)->For = mGui_ptr->Get("FormForInput")->Text.at("Input").Text;

	if (mGui_ptr->Get("FormTypeInput")->Text.at("Input").Text == "Input")
	{
		Str tmp;
		tmp.Scale = 1.0;
		tmp.Color = glm::vec4(1, 1, 1, 1);
		tmp.Text = "Input";
		auto forPos = mGui_ptr->Get(mGui_ptr->Get("FormForInput")->Text.at("Input").Text);
		tmp.Position = forPos->Position;
		mGui_ptr->Get(*mFormName_ptr)->Text.emplace("Input", tmp);
	}

	mGui_ptr->Get(*mFormName_ptr)->Visible = std::stoi(mGui_ptr->Get("FormVisibleInput")->Text.at("Input").Text);

	
	auto ShowToClick = Reader::getInstance()->split(mGui_ptr->Get("FormShowInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->ShowToClick.clear();
	for (auto& i : ShowToClick)
		mGui_ptr->Get(*mFormName_ptr)->ShowToClick.push_back(i);

	auto HideToClick = Reader::getInstance()->split(mGui_ptr->Get("FormHideInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->HideToClick.clear();
	for (auto& i : HideToClick)
		mGui_ptr->Get(*mFormName_ptr)->HideToClick.push_back(i);

	if (!mGui_ptr->Get("FormHotKeyInput")->Text.at("Input").Text.empty())
	{
		mGui_ptr->Get(*mFormName_ptr)->Key.first = true;
		mGui_ptr->Get(*mFormName_ptr)->Key.second = (char)mGui_ptr->Get("FormHotKeyInput")->Text.at("Input").Text.c_str()[0];
	}

	mGui_ptr->Get(*mFormName_ptr)->CommandOnClick.first = mGui_ptr->Get("FormCommandInput")->Text.at("Input").Text;
		
	if (!mGui_ptr->Get("FormActHighInput")->Text.at("Input").Text.empty())
		mGui_ptr->Get(*mFormName_ptr)->ActiveHighlight = std::stoi(mGui_ptr->Get("FormActHighInput")->Text.at("Input").Text);

	if (!mGui_ptr->Get("FormActIntenInput")->Text.at("Input").Text.empty())
		mGui_ptr->Get(*mFormName_ptr)->ActiveHighlight = std::stof(mGui_ptr->Get("FormActIntenInput")->Text.at("Input").Text);

	auto Padding = Reader::getInstance()->split(mGui_ptr->Get("FormPaddingInput")->Text.at("Input").Text, " ");
	mGui_ptr->Get(*mFormName_ptr)->Padding.x = std::stof(Padding[0]);
	mGui_ptr->Get(*mFormName_ptr)->Padding.y = std::stof(Padding[1]);
}
