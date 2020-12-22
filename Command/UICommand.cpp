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
