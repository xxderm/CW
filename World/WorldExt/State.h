#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER
#include "Province.h"
#include "../../Reader.h"

struct StateFormat
{
	std::string Name;
	std::string CountryTag;
	std::vector<std::string> Provinces;
	int Id;
};


class State final 
{
public:
	State();
	const StateFormat& getState(int Id);
	void setState(int Id, StateFormat state);
	void Init(Province* province);
private:
	std::vector<StateFormat> mStates;
};

#endif // !STATE_HEADER
