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
	State(std::unique_ptr<IWorld> world);
	void Create() override;
	const StateFormat& getState(int Id);
	void setState(int Id, StateFormat state);
private:
	void Init();
private:
	std::vector<StateFormat> mStates;
	std::unique_ptr<IWorld> mProvinces;
};

#endif // !STATE_HEADER
