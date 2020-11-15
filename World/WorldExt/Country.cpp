#include "Country.h"

Country::Country()
{
}

void Country::Init()
{
	std::vector<std::string> TagFiles;
	Reader::getInstance()->getFiles("Resources/TAG/*", TagFiles);

	for (std::string& FileName : TagFiles)
	{ 
		std::string TAG = {FileName[0] , FileName[1] , FileName[2]};
		auto Capital = (Reader::getInstance()->getValue("Resources/TAG/" + FileName, "capital", 3, true));
		CountryFormat country;
		country.Tag = TAG;
		country.Capital = std::stoi(Capital);
		mCountries.try_emplace(TAG, country);
	}

	auto CountryFiles = Reader::getInstance()->getFileLines("Resources/00_countries.txt");
	for (auto& file : CountryFiles)
	{

	}
}
