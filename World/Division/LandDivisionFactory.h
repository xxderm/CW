#pragma once
#ifndef LAND_DIVISION_FACTORY_HEADER
#define LAND_DIVISION_FACTORY_HEADER
#include "DivisionFactory.h"
#include "InfantryLandDivision.h"
#include "TankLandDivision.h"

class LandDivisionFactory final : public DivisionFactory<LandDivision>
{
public:
	LandDivision* Create(DIVISION_TYPE type) override;
};

#endif // !LAND_DIVISION_FACTORY_HEADER
