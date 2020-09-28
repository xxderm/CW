#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER
#include "WorldDecorator.h"
#include "Province.h"
#include "../../Reader.h"

struct StateFormat
{
	std::string Name;
	std::vector<std::string> Provinces;
	int Id;
};

class State final : public WorldDecorator
{
public:
	State(World* world);
	void Init(Province* Provinces);
private:
	std::vector<StateFormat> mStates;
};

#endif // !STATE_HEADER
