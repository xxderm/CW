#pragma once
#ifndef WORLD_HEADER
#define WORLD_HEADER
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <time.h>
#include <glm/detail/_noise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <boost/thread.hpp>
#include "easylogging++.h"
#include <boost/thread.hpp>
#include "DataTypes/DataTypes.h"

class World final 
{
	std::vector<Diplomatic> mDiplomatics;
	std::vector<Purchase> mPurchases;
	std::vector<Embargo> mEmbargoes;
	std::vector<NonAggressionPact> mNonAggressionPacts;
	std::vector<Stocks> mStocks;
	std::vector<Loan> mLoans;
	std::unordered_map<std::string, Union> mUnions;
public:
	World();
	void Create();
	void Update();
	Country* getCountries();
	Province* getProvinces();
	State* getStates();
	auto getDiplomatics() -> decltype(mDiplomatics);
	auto getPurchases() -> decltype(mPurchases);
	auto getEmbargoes() -> decltype(mEmbargoes);
	auto getNonAggressionPacts() -> decltype(mNonAggressionPacts);
	auto getStocks() -> decltype(mStocks);
	auto getLoans() -> decltype(mLoans);
	auto getUnion() -> decltype(mUnions);
private:
	Country* mCountry;
	Province* mProvince;
	State* mState;
	boost::posix_time::ptime mDate;
};

#endif


