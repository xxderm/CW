#pragma once
#ifndef READER_HEADER
#define READER_HEADER
#include <vector>
#include <string>
#include <fstream>
#include "easylogging++.h"
#include "Renderer/RenderExt/GUITexture.h"
#include <locale>
#include <codecvt>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/locale.hpp>

#define GET_IFSTREAM_CHAR(code) while(getline(f, mCurrentLine)){std::string tmp;for (auto& c : mCurrentLine){tmp += c;		tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end()); code }}

class Reader
{
public:
	std::vector<std::string> getArray(std::string Path, std::string Keyword, bool isDigit = 0);
	std::vector<std::string> get2DArray(std::string Path, std::string Keyword, std::string key, std::string sep = " ", bool isDigit = 0);
	std::vector<std::string> getFileLines(std::string Path);
	std::vector<std::string> getLangLines(std::string Path, std::string Keyword, std::string sep = "_");
	std::string getValue(std::string Path, std::string Keyword, int seek = 0, bool digit = 0, bool skipws = true);
	void getUI(GUITexture* guis, std::string path, bool update = 1);
#ifdef _WIN32
	void getFiles(std::string Path, std::vector<std::string>& Src);
#endif
	static Reader* getInstance()
	{
		return &mReader;
	}
	std::vector<std::string> split(const std::string& str, const std::string& delim);
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


