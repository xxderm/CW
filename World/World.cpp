#include "World.h"

World::World()
{
	mCountry = new Country();
	mProvince = new Province();
	mState = new State();
}

void World::Create()
{
	auto start = clock();
	boost::thread provThread(&Province::Init, mProvince);
	boost::thread countryThread(&Country::Init, mCountry);
	boost::thread_group tg;
	tg.add_thread(&provThread);
	tg.add_thread(&countryThread);
	tg.join_all();
	mState->Init(mProvince);
	tg.remove_thread(&countryThread);
	tg.remove_thread(&provThread);

	mDate = { 
		boost::gregorian::date(1936, boost::gregorian::Jun, 12),
		boost::posix_time::hours(12) 
	};
}

void World::Update()
{
}

Country* World::getCountries()
{
	return mCountry;
}

Province* World::getProvinces()
{
	return mProvince;
}

State* World::getStates()
{
	return mState;
}

auto World::getDiplomatics() -> decltype(mDiplomatics)
{
	return mDiplomatics;
}

auto World::getPurchases() -> decltype(mPurchases)
{
	return mPurchases;
}

auto World::getEmbargoes() -> decltype(mEmbargoes)
{
	return mEmbargoes;
}

auto World::getNonAggressionPacts() -> decltype(mNonAggressionPacts)
{
	return mNonAggressionPacts;
}

auto World::getStocks() -> decltype(mStocks)
{
	return mStocks;
}

auto World::getLoans() -> decltype(mLoans)
{
	return mLoans;
}

auto World::getUnion() -> decltype(mUnions)
{
	return mUnions;
}
