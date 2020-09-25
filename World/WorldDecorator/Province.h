#pragma once
#ifndef PROVINCE_HEADER
#define PROVINCE_HEADER
#include "WorldDecorator.h"

class Province final : public WorldDecorator
{
public:
	Province(World* world);
};

#endif // !PROVINCE_HEADER
