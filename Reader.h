#pragma once
#ifndef READER_HEADER
#define READER_HEADER
#include <vector>
#include <string>
#include <fstream>
#include "easylogging++.h"

#define GET_IFSTREAM_CHAR(code) while(getline(f, mCurrentLine)){std::string tmp;for (auto& c : mCurrentLine){tmp += c;		tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end()); code }}

class Reader
{
public:
	std::vector<std::string> getArray(std::string Path, std::string Keyword);
	std::string getValue(std::string Path, std::string Keyword);

	static Reader* getInstance()
	{
		return &mReader;
	}
private:
	std::ifstream getStream(std::string Path);	
	void Clean();
private:
	static Reader mReader;
	std::string mCurrentLine = "";
	std::string mLiteral = "";
	bool mCheck = false;
};

#endif // !READER_HEADER


