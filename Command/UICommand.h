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

#endif // !UI_COMMAND_HEADER
