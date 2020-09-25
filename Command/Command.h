#pragma once
#ifndef COMMAND_HEADER
#define COMMAND_HEADER

class Command abstract
{
public:
	virtual void Execute() = 0;
};

#endif // !COMMAND_HEADER
