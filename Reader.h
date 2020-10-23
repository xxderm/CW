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

#define GET_IFSTREAM_CHAR(code) while(getline(f, mCurrentLine)){std::string tmp;for (auto& c : mCurrentLine){tmp += c;		tmp.erase(std::remove(tmp.begin(), tmp.end(), '\t'), tmp.end()); code }}

class Reader
{
public:
	std::vector<std::string> getArray(std::string Path, std::string Keyword);
	std::string getValue(std::string Path, std::string Keyword, int seek = 0);
	void getUI(GUITexture* guis, std::string path, bool update = 1);
#ifdef _WIN32
	void getFiles(std::string Path, std::vector<std::string>& Src);
#endif
	static Reader* getInstance()
	{
		return &mReader;
	}
private:
	std::ifstream getStream(std::string Path);	
	void Clean();
	std::vector<std::string> split(const std::string& str, const std::string& delim);
private:
	static Reader mReader;
	std::string mCurrentLine = "";
	std::string mLiteral = "";
	bool mCheck = false;
};

#endif // !READER_HEADER


