#pragma once
#ifndef WAR_COMMAND_HEADER
#define WAR_COMMAND_HEADER
#include "Command.h"

class DeclWarCommand final : public Command
{
public:
	DeclWarCommand();
	void Execute() override;
	~DeclWarCommand();
};

class CapitulateCommand final : public Command
{
public:
	CapitulateCommand();
	void Execute() override;
	~CapitulateCommand();
};

class NuclearStrikeCommand final : public Command
{
public:
	NuclearStrikeCommand();
	void Execute() override;
	~NuclearStrikeCommand();
};

#endif // !WARCOMMAND_HEADER
