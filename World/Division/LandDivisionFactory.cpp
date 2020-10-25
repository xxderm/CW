#include "LandDivisionFactory.h"

LandDivision* LandDivisionFactory::Create(DIVISION_TYPE type)
{
	switch (type)
	{
    case DIVISION_TYPE::INFANTRY:
        return new InfantryLandDivision();
        break;
    case DIVISION_TYPE::TANK:
        return new TankLandDivision();
        break;   
    default:
        break;
	}
}
