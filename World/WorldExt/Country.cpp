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
		CountryFormat country;
		country.Tag = TAG;
		mCountries.try_emplace(TAG, country);
	}
}
