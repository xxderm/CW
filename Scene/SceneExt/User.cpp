#include "User.h"

User::User()
{
}

const std::string User::getName()
{
	return mName;
}

const std::string User::getCountryTag()
{
	return mCountryTag;
}

const std::string User::getLobbyName()
{
	return mLobbyName;
}

const bool User::isConnected()
{
	return mConnected;
}

const long User::getPing()
{
	return mPing;
}

const uint32_t User::getId()
{
	return mId;
}

void User::setName(std::string Name)
{
	this->mName = Name;
}

void User::setCountryTag(std::string Tag)
{
	this->mCountryTag = Tag;
}

void User::setPing(long Ping)
{
	this->mPing = Ping;
}

void User::setId(uint32_t Id)
{
	this->mId = Id;
}

void User::setConnected(bool v)
{
	this->mConnected = v;
}

void User::setLobbyName(std::string name)
{
	this->mLobbyName = name;
}

User::~User()
{
}
