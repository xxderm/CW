#pragma once
#ifndef WORLD_DECORATOR_HEADER
#define WORLD_DECORATOR_HEADER
#include "../World.h"

class WorldDecorator : public World
{
public:
	WorldDecorator(World* world);
protected:
	World* mWorld;
};

#endif // !WORLDDECORATOR_HEADER
