#include "Country.h"

Country::Country()
{

}

void Country::Init()
{
	if (!this->Load("Resources/cache/countriesdata"))
	{
		std::vector<std::string> TagFiles;
		Reader::getInstance()->getFiles("Resources/TAG/*", TagFiles);

		for (std::string& FileName : TagFiles)
		{
			std::string TAG = { FileName[0] , FileName[1] , FileName[2] };
			auto Capital = (Reader::getInstance()->getValue("Resources/TAG/" + FileName, "capital", 3, true));
			auto RulingParty = (Reader::getInstance()->getValue("Resources/TAG/" + FileName, "ruling_party", 3));
			if (RulingParty.size() == 0)
				RulingParty = "neutrality";
			CountryFormat* country = new CountryFormat();
			country->Tag = TAG;
			country->Capital = std::stoi(Capital);
			country->RulingParty = RulingParty;



			auto names = Reader::getInstance()->getLangLines("Resources/lang/countries_l_russian.yml", TAG);
			for (auto& name : names)
			{
				auto countryName = Reader::getInstance()->split(name, ":")[1];
				LangFormatText(countryName);
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

			auto PartyNames = Reader::getInstance()
				->getLangLines("Resources/lang/parties_l_russian.yml",
					TAG + "_" + country->RulingParty + "_party", ":");
			if (PartyNames.size() > 0 && country->RulingParty.size() > 0)
			{
				auto PartyName = Reader::getInstance()->split(PartyNames[0], ":")[1];
				LangFormatText(PartyName);
				country->PartyName = PartyName;
			}
			else if (country->RulingParty.size() > 0)
			{
				PartyNames = Reader::getInstance()
					->getLangLines("Resources/lang/parties_l_russian.yml",
						country->RulingParty, ":");
				auto PartyName = Reader::getInstance()->split(PartyNames[0], ":")[1];
				LangFormatText(PartyName);
				country->PartyName = PartyName;
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

		this->Save("Resources/cache/countriesdata");
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

void Country::Save(std::string Path)
{
	std::ofstream save;
	save.open(Path);
	save << mCountries.size() << std::endl;
	for (auto& country : mCountries)
	{
		save << country.first << std::endl;
		save << country.second->Capital << std::endl;
		save << country.second->Color.r << std::endl;
		save << country.second->Color.g << std::endl;
		save << country.second->Color.b << std::endl;
		save << country.second->Name.size() << std::endl;
		for (auto& name : country.second->Name)
		{
			save << name.first << std::endl;
			save << name.second << std::endl;
		}
		save << country.second->NameADJ.size() << std::endl;
		for (auto& name : country.second->NameADJ)
		{
			save << name.first << std::endl;
			save << name.second << std::endl;
		}
		save << country.second->NameDEF.size() << std::endl;
		for (auto& name : country.second->NameDEF)
		{
			save << name.first << std::endl;
			save << name.second << std::endl;
		}	
		save << country.second->PartyName << std::endl;
		save << country.second->RulingParty << std::endl;
		save << country.second->Tag << std::endl;
	}
	save << mCountriesColor.size() << std::endl;
	for (auto& country : mCountriesColor)
	{
		save << country.first << std::endl;
		save << country.second->Tag << std::endl;
	}
	save.close();
}

bool Country::Load(std::string Path)
{
	std::ifstream load;
	load.open(Path);
	if(!load.is_open())
		return false;	
	int countrySize;
	load >> countrySize;
	for (size_t i = 0; i < countrySize; i++)
	{
		std::string Tag;
		load >> Tag;
		CountryFormat* country = new CountryFormat();
		load >> country->Capital;
		load >> country->Color.r;
		load >> country->Color.g;
		load >> country->Color.b;
		int nameSize;
		load >> nameSize;
		for (size_t j = 0; j < nameSize; j++)
		{
			std::string partyName;
			std::string partyTitle;
			load >> partyName;
			std::getline(load, partyTitle);
			std::getline(load, partyTitle);
			country->Name.emplace(partyName, partyTitle);
		}
		load >> nameSize;
		for (size_t j = 0; j < nameSize; j++)
		{
			std::string partyName;
			std::string partyTitle;
			load >> partyName;
			std::getline(load, partyTitle);
			std::getline(load, partyTitle);
			country->NameADJ.emplace(partyName, partyTitle);
		}
		load >> nameSize;
		for (size_t j = 0; j < nameSize; j++)
		{
			std::string partyName;
			std::string partyTitle;
			load >> partyName;
			std::getline(load, partyTitle);
			std::getline(load, partyTitle);
			country->NameDEF.emplace(partyName, partyTitle);
		}
		std::getline(load, country->PartyName);
		load >> country->RulingParty;
		load >> country->Tag;
		mCountries.emplace(Tag, country);
	}
	load >> countrySize;
	for (size_t i = 0; i < countrySize; i++)
	{
		std::string Color;
		std::string Tag;
		load >> Color;
		load >> Tag;
		if (Tag.size() > 0 && Color.size() > 0)
		{
			mCountriesColor.emplace(Color, mCountries.at(Tag));
		}
	}
	load.close();
	return true;
}

void Country::LangFormatText(std::string& text)
{
	text.erase(std::remove(text.begin(), text.end(), '0'));
	text.erase(std::remove(text.begin(), text.end(), '\"'));
	text.erase(std::remove(text.begin(), text.end(), '"'));
	text.erase(text.begin());
}

std::string CountryFormat::getName()
{
	return Name.at(RulingParty);
}

std::string CountryFormat::getNameDEF()
{
	return NameDEF.at(RulingParty);
}

std::string CountryFormat::getNameADJ()
{
	return NameADJ.at(RulingParty);
}
