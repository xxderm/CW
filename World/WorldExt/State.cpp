#include "State.h"

State::State()	
{
}


void State::Init(Province* province)
{
	std::vector<std::string> stateFiles;
	Reader::getInstance()->getFiles("Resources/states/*", stateFiles);
		
	for (size_t i = 0; i < stateFiles.size(); i++)
	{
		StateFormat* state = new StateFormat();
		state->Id = std::stoi(
			Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "id")
		);
		state->Name = Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "name");
		state->Provinces = Reader::getInstance()->getArray("Resources/states/" + stateFiles.at(i), "provinces");
		state->CountryTag = Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "owner");
		for (size_t j = 0; j < state->Provinces.size(); j++)
		{			
			ProvinceFormat* currentProvince = province->getProvince(std::stoi(state->Provinces.at(j)));
			currentProvince->StateId = state->Id;
			//province->setProvince(std::stoi(state.Provinces.at(j)), currentProvince);
		}
		mStates.emplace(state->Id, state);
	}

	stateFiles.clear();
}

StateFormat* State::getState(int Id)
{
	return mStates.at(Id);
}

void State::setState(int Id, StateFormat* state)
{
	mStates.at(Id) = state;
}
