#pragma once
#ifndef COUNTRY_HEADER
#define COUNTRY_HEADER
#include "WorldDecorator.h"

struct CountryFormat
{
	std::string Tag;
};

class Country final : public WorldDecorator
{
public:
	Country(World* world);
	void Init();
private:
	std::map<std::string, CountryFormat> mCountries;
};

#endif // !COUNTRY_HEADER
