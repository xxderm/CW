#pragma once
#ifndef POLITICAL_COMMAND_HEADER
#define POLITICAL_COMMAND_HEADER
#include "Command.h"

class CreateUnionCommand final : public Command
{
public:
	CreateUnionCommand();
	void Execute() override;
	~CreateUnionCommand();
};

class AddUnionCommand final : public Command
{
public:
	AddUnionCommand();
	void Execute() override;
	~AddUnionCommand();
};

class LeaveUnionCommand final : public Command
{
public:
	LeaveUnionCommand();
	void Execute() override;
	~LeaveUnionCommand();
};

class NonAgressPactCommand final : public Command
{
public:
	NonAgressPactCommand();
	void Execute() override;
	~NonAgressPactCommand();
};

#endif // !POLITICALCOMMAND_HEADER
