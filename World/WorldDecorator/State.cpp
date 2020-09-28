#include "State.h"

State::State(World* world)
	: WorldDecorator(world)
{
}

void State::Init(Province* Provinces)
{
	std::vector<std::string> stateFiles;
	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;
	hFind = FindFirstFileA("Resources/states/*", &FindFileData);
	while (FindNextFileA(hFind, &FindFileData) != NULL)
		stateFiles.push_back(FindFileData.cFileName);
	stateFiles.erase(stateFiles.begin());
	FindClose(hFind);
	
	for (size_t i = 0; i < stateFiles.size(); i++)
	{
		StateFormat state;
		state.Id = std::stoi(
			Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "id")
		);
		state.Name = Reader::getInstance()->getValue("Resources/states/" + stateFiles.at(i), "name");
		state.Provinces = Reader::getInstance()->getArray("Resources/states/" + stateFiles.at(i), "provinces");
		for (size_t j = 0; j < state.Provinces.size(); j++)
		{
			auto currentProvince = Provinces->getProvince(std::stoi(state.Provinces.at(j)));
			currentProvince.StateId = state.Id;
			Provinces->setProvince(std::stoi(state.Provinces.at(j)), currentProvince);
		}
	}

	stateFiles.clear();
}
