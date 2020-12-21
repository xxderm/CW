#pragma once
#ifndef COUNTRY_HEADER
#define COUNTRY_HEADER
#include <vector>
#include <string>
#include <map>
#include "../../Reader.h"

struct CountryFormat
{
	std::string Tag;
	glm::vec3 Color;
	int Capital;
};

class Country final 
{
public:
	Country();
	void Init();
	CountryFormat* getCountryByTag(std::string Tag);
	CountryFormat* getCountryByColor(std::string Color);
private:
	std::map<std::string, CountryFormat*> mCountries;	
	std::map<std::string, CountryFormat*> mCountriesColor;
};

#endif // !COUNTRY_HEADER
