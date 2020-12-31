#pragma once
#ifndef COUNTRY_HEADER
#define COUNTRY_HEADER
#include <vector>
#include <string>
#include <map>
#include "../../Reader.h"
#include "../Division/LandDivision.h"
#include "../Division/AirDivision.h"
#include "../Division/NavalDivision.h"

struct CountryFormat
{
	std::string getName();
	std::string getNameDEF();
	std::string getNameADJ();
	std::string Tag;
	std::string RulingParty;
	std::string PartyName;
	std::string LeaderName;
	glm::vec3 Color;
	int Capital;

	std::unordered_map<std::string, std::string> Name;
	std::unordered_map<std::string, std::string> NameDEF;
	std::unordered_map<std::string, std::string> NameADJ;

	std::unordered_map<std::string, LandDivision*> LandDiv;
	std::unordered_map<std::string, AirDivision*> AirDiv;
	std::unordered_map<std::string, NavalDivision*> NavDiv;
};

class Country final 
{
public:
	Country();
	void Init();
	CountryFormat* getCountryByTag(std::string Tag);
	CountryFormat* getCountryByColor(std::string Color);
	void Save(std::string Path);
	bool Load(std::string Path);
private:
	void LangFormatText(std::string& text);
private:
	std::map<std::string, CountryFormat*> mCountries;	
	std::map<std::string, CountryFormat*> mCountriesColor;
};

#endif // !COUNTRY_HEADER
