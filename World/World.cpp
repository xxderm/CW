#include "World.h"

World::World()
{
	mCountry = new Country();
	mProvince = new Province();
	mState = new State();
}

void World::Create()
{
	boost::thread provThread(&Province::Init, mProvince);
	boost::thread countryThread(&Country::Init, mCountry);
	boost::thread_group tg;
	tg.add_thread(&provThread);
	tg.add_thread(&countryThread);
	tg.join_all();
	mState->Init(mProvince);
	tg.remove_thread(&countryThread);
	tg.remove_thread(&provThread);
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
