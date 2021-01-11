#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER
#include "Province.h"
#include "../../Reader.h"

enum BuildingType
{
	CHURCH,
	CATHEDRAL,
	UNIVERSITY,
	SHIPYARD,
	BARRACKS,
	MILITARY_FACTORY,
	CIVILIAN_FACTORY,
	MARKET,
	WORKSHOP,
	TOWN_HALL,
	MANPOWER,
	RESISTANCE,
	MAX
};

struct StateFormat
{
	std::string Name;
	std::string CountryTag;
	std::vector<std::string> Provinces;
	int Id;	
	
	int Buildings[BuildingType::MAX]{ 0 };
	float ManpowerIncrease;
	float ResistanceIncrease;
};

class State final 
{
public:
	State();
	StateFormat* getState(int Id);
	void setState(int Id, StateFormat* state);
	void Init(Province* province);
private:
	std::unordered_map<int, StateFormat*> mStates;
};

#endif // !STATE_HEADER
