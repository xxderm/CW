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
