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

		auto names = Reader::getInstance()->getLangLines("Resources/lang/countries_l_russian.yml", TAG);
		for (auto& name : names)
		{
			auto countryName = Reader::getInstance()->split(name, ":")[1];
			countryName.erase(std::remove(countryName.begin(), countryName.end(), '0'));
			countryName.erase(std::remove(countryName.begin(), countryName.end(), '\"'));
			countryName.erase(std::remove(countryName.begin(), countryName.end(), '"'));
			countryName.erase(countryName.begin());
			auto countryLit = Reader::getInstance()->split(name, "_");
			countryLit[0].erase(std::remove(countryLit[0].begin(), countryLit[0].end(), ' '));
			countryLit[1] = Reader::getInstance()->split(countryLit[1], ":")[0];
			if (countryLit.size() == 2)
				country->Name.emplace(countryLit[1], countryName);
			else
			{
				if (Reader::getInstance()->split(countryLit.at(2), ":")[0] == "DEF")
					country->NameDEF.emplace(countryLit[1], countryName);
				else
					country->NameADJ.emplace(countryLit[1], countryName);
			}
		}

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

		mCountriesColor.emplace(
			std::to_string(int(mCountries.at(TAG)->Color.r)) + std::to_string(int(mCountries.at(TAG)->Color.g)) + std::to_string(int(mCountries.at(TAG)->Color.b))
			, mCountries.at(TAG));
	}
}

CountryFormat* Country::getCountryByTag(std::string Tag)
{
	return mCountries.at(Tag);
}

/*
* Принимает строку в виде R + G + B
*/
CountryFormat* Country::getCountryByColor(std::string Color)
{
	if (mCountriesColor.count(Color) > 0)
		return mCountriesColor.at(Color);
	return nullptr;
}

const std::string CountryFormat::getName()
{
	return Name.at(RulingParty);
}

const std::string CountryFormat::getNameDEF()
{
	return NameDEF.at(RulingParty);
}

const std::string CountryFormat::getNameADJ()
{
	return NameADJ.at(RulingParty);
}
