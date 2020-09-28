#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER
#include "WorldDecorator.h"
#include "Province.h"

struct StateFormat
{
	std::string Name;
	std::string CountryTag;
	std::vector<std::string> Provinces;
	int Id;
};

class State final : public WorldDecorator
{
public:
	State(World* world);
	void Init(Province* Provinces);
	const StateFormat& getState(int Id);
	void setState(int Id, StateFormat state);
private:
	std::vector<StateFormat> mStates;
};

#endif // !STATE_HEADER
