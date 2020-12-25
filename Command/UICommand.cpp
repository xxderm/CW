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
	}
}
