#include "NavalDivisionFactory.h"

NavalDivision* NavalDivisionFactory::Create(DIVISION_TYPE type)
{
	switch (type)
	{
	case DIVISION_TYPE::DESTROYER:
		return new DestroyerNavalDivision();
		break;
	case DIVISION_TYPE::BATTLESHIP:
		return new BattleshipNavalDivision();
		break;
	case DIVISION_TYPE::AEROCARRIER:
		return new AerocarrierNavalDivision();
		break;
	default:
		return nullptr;
		break;
	}
}
