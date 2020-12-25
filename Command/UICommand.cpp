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
	format->Name = "Form" + std::to_string(mGui_ptr->getGui().size());
	format->Visible = true;
	format->Moveable = true;
	format->TextureId = -1;
	format->Position = glm::vec2(0.0, 0.0);
	format->Color = glm::vec4(1.0, 1.0, 1.0, 1.0);
	format->hoverColor = format->Color;
	format->Scale = glm::vec2(0.3, 0.6);
	mGui_ptr->Add(format->Name, format, true);
}
