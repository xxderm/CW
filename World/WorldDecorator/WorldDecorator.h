#pragma once
#ifndef WORLD_DECORATOR_HEADER
#define WORLD_DECORATOR_HEADER
#include "../World.h"
#include "../../Reader.h"

class WorldDecorator abstract : public World
{
public:
	WorldDecorator(World* world);
protected:
	World* mWorld;
};

#endif // !WORLDDECORATOR_HEADER
