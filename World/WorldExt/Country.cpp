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
		CountryFormat* country = new CountryFormat();
		country->Tag = TAG;
		country->Capital = std::stoi(Capital);
		mCountries.try_emplace(TAG, country);
	}

	auto CountryFiles = Reader::getInstance()->getFileLines("Resources/00_countries.txt");
	for (auto& file : CountryFiles)
	{
		std::string TAG = { file[0] , file[1] , file[2] };
		auto color = Reader::getInstance()->get2DArray("Resources/countries/colors.txt", TAG, "color", " ", 1);
		if (color.size() == 0)
		{
			std::string FileStr = std::strchr(file.c_str(), '\"');
			FileStr.erase(std::remove(FileStr.begin(), FileStr.end(), '\t'));
			FileStr.erase(std::remove(FileStr.begin(), FileStr.end(), '\"'));
			FileStr.erase(std::remove(FileStr.begin(), FileStr.end(), '"'));
			color = Reader::getInstance()->getArray("Resources/" + FileStr, "color", true);
		}
		mCountries.at(TAG)->Color = glm::vec3(std::stoi(color[color.size() - 3]), std::stoi(color[color.size() - 2]), std::stoi(color[color.size() - 1]));
	}
}

CountryFormat* Country::getCountryByTag(std::string Tag)
{
	return mCountries.at(Tag);
}
