#pragma once
#ifndef USER_HEADER
#define USER_HEADER
#include <SDL_net.h>
#include <unordered_map>
#include <string>
#include "easylogging++.h"
#include "../../World/WorldExt/Country.h"

class User final
{
public:
	User();
	const std::string getName();
	const std::string getLobbyName();
	const CountryFormat* getCountry();
	const bool isConnected();
	const long getPing();
	const uint32_t getId();
	void setName(std::string Name);
	void setPing(long Ping);
	void setId(uint32_t Id);
	void setConnected(bool v);
	void setLobbyName(std::string name);
	void setCountry(CountryFormat* country);
	~User();
private:
	std::string mName;
	CountryFormat* mCountry;
	std::string mLobbyName;
	long mPing;
	uint32_t mId;
	bool mConnected = false;
};

#endif // !USER_HEADER
