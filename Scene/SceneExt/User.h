#pragma once
#ifndef USER_HEADER
#define USER_HEADER
#include <SDL_net.h>
#include <unordered_map>
#include <string>
#include "easylogging++.h"

class User final
{
public:
	User();
	const std::string getName();
	const std::string getCountryTag();
	const std::string getLobbyName();
	const bool isConnected();
	const long getPing();
	const uint32_t getId();
	void setName(std::string Name);
	void setCountryTag(std::string Tag);
	void setPing(long Ping);
	void setId(uint32_t Id);
	void setConnected(bool v);
	void setLobbyName(std::string name);
	~User();
private:
	std::string mName;
	std::string mCountryTag;
	std::string mLobbyName;
	long mPing;
	uint32_t mId;
	bool mConnected = false;
};

#endif // !USER_HEADER
