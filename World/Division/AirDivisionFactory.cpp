#include "AirDivisionFactory.h"

AirDivision* AirDivisionFactory::Create(DIVISION_TYPE type)
{
	switch (type)
	{    
    case DIVISION_TYPE::FIGHTER:
        return new FighterAirDivision();
        break;
    case DIVISION_TYPE::STORMTROOPER:
        return new StrormtrooperAirDivision();
        break;
    case DIVISION_TYPE::BOMBER:
        return new BomberAirDivision();
        break;   
    default:
        return nullptr;
        break;
	}
}
