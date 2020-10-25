#pragma once
#ifndef DIVISION_FACTORY_HEADER
#define DIVISION_FACTORY_HEADER

enum class DIVISION_TYPE
{
	// LAND
	INFANTRY,
	TANK,

	// AIR
	FIGHTER,
	STORMTROOPER,
	BOMBER,

	// NAVAL
	DESTROYER,
	BATTLESHIP,
	AEROCARRIER,
};

template<typename T>
class DivisionFactory abstract
{
public:
	virtual T* Create(DIVISION_TYPE) = 0;
};

#endif // !DIVISION_FACTORY_HEADER
