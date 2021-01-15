#include "User.h"

User::User()
{
}

const std::string User::getName()
{
	return mName;
}

const std::string User::getLobbyName()
{
	return mLobbyName;
}

const CountryFormat* User::getCountry()
{
	return mCountry;
}

const CountryFormat* User::getSelectedCountry()
{
	return mSelectedCountry;
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

const UserState User::getStatus()
{
	return mStatus;
}

void User::setName(std::string Name)
{
	this->mName = Name;
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

void User::setCountry(CountryFormat* country)
{
	this->mCountry = country;
}

void User::setSelectedCountry(CountryFormat* country)
{
	this->mSelectedCountry = country;
}

void User::setStatus(UserState status)
{
	this->mStatus = status;
}

User::~User()
{
}
