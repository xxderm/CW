#pragma once
#ifndef COMMAND_HEADER
#define COMMAND_HEADER
class Command abstract
{
public:
	virtual void Execute() = 0;
	virtual ~Command() = 0;
};

class DoCommand : public Command
{
public:
	DoCommand(int x, int y) : x(x), y(y) {}
	void Execute() override
	{

	}
private:
	int x, y;
};

void baz()
{
	Command* toDo = new DoCommand(10, 20);
	toDo->Execute();
}
#endif // !COMMAND_HEADER
