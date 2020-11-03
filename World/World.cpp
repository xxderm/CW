#include "World.h"

World::World()
{
	mCountry = std::make_unique<Country>();
	mProvince = std::make_unique<Province>();
	mState = std::make_unique<State>();
}

void World::Create()
{
	boost::thread provThread(&Province::Init, mProvince.get());
	boost::thread countryThread(&Country::Init, mCountry.get());
	boost::thread_group tg;
	tg.add_thread(&provThread);
	tg.add_thread(&countryThread);
	tg.join_all();
	mState->Init(mProvince.get());
	tg.remove_thread(&countryThread);
	tg.remove_thread(&provThread);
}
