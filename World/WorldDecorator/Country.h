#pragma once
#ifndef COUNTRY_HEADER
#define COUNTRY_HEADER
#include "WorldDecorator.h"

class Country final : public WorldDecorator
{
public:
	Country(World* world);
};

#endif // !COUNTRY_HEADER
