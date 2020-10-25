#pragma once
#ifndef AIR_DIVISION_FACTORY_HEADER
#define AIR_DIVISION_FACTORY_HEADER
#include "DivisionFactory.h"
#include "FighterAirDivision.h"
#include "StormtrooperAirDivision.h"
#include "BomberAirDivision.h"

class AirDivisionFactory final : public DivisionFactory<AirDivision> 
{
public:
	AirDivision* Create(DIVISION_TYPE type) override;
};

#endif // !AIR_DIVISION_FACTORY_HEADER
