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
	~User();
private:
	uint32_t Id;
	std::string Name;
	long Ping;
};

#endif // !USER_HEADER
