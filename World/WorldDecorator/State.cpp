#include "State.h"

State::State(World* world)
	: WorldDecorator(world)
{
}

void State::Init(Province* Provinces)
{
	std::vector<std::string> stateFiles;
	Reader::getInstance()->getFiles("Resources/states/*", stateFiles);
		
	for (size_t i = 0; i < stateFiles.size(); i++)
	{
		StateFormat state;
		state.Id = std::stoi(
			Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "id")
		);
		state.Name = Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "name");
		state.Provinces = Reader::getInstance()->getArray("Resources/states/" + stateFiles.at(i), "provinces");
		state.CountryTag = Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "owner");
		for (size_t j = 0; j < state.Provinces.size(); j++)
		{
			auto currentProvince = Provinces->getProvince(std::stoi(state.Provinces.at(j)));
			currentProvince.StateId = state.Id;
			Provinces->setProvince(std::stoi(state.Provinces.at(j)), currentProvince);
		}
		mStates.push_back(state);
	}

	stateFiles.clear();
}

const StateFormat& State::getState(int Id)
{
	return mStates.at(Id);
}

void State::setState(int Id, StateFormat state)
{
	mStates.at(Id) = state;
}
