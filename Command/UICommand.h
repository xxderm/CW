#pragma once
#ifndef UI_COMMAND_HEADER
#define UI_COMMAND_HEADER
#include "Command.h"

class ExitCommand final : public Command
{
public:
	ExitCommand(Scene* scene);
	void Execute() override;
private:
	Scene* mScene_ptr;
};

class ChangeSceneCommand final : public Command
{
public:
	ChangeSceneCommand(Scene* src, SceneMachine* dst);
	void Execute() override;
private:
	Scene* mScene_ptr;
	SceneMachine* mSceneMachine_ptr;
};

class ClearLobbyListCommand final : public Command
{
public:
	ClearLobbyListCommand(std::vector<Lobby>* lobbies);
	void Execute() override;
private:
	std::vector<Lobby>* mLobbies;
};

#endif // !UI_COMMAND_HEADER
