#pragma once
#ifndef NAVAL_DIVISION_FACTORY_HEADER
#define NAVAL_DIVISION_FACTORY_HEADER
#include "DivisionFactory.h"
#include "NavalDivision.h"
#include "DestroyerNavalDivision.h"
#include "BattleshipNavalDivision.h"
#include "AerocarrierNavalDivision.h"

class NavalDivisionFactory final  : public DivisionFactory<NavalDivision>
{
public:	
	NavalDivision* Create(DIVISION_TYPE type) override;
};

#endif // !NAVAL_DIVISION_FACTORY_HEADER
