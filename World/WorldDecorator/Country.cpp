#include "Country.h"

Country::Country(std::unique_ptr<IWorld> world)
	: WorldDecorator{ std::move(world) }
{
}

void Country::Create()
{
	WorldDecorator::Create();
	// TODO: Add provinces
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
