#pragma once
#ifndef WORLD_DECORATOR_HEADER
#define WORLD_DECORATOR_HEADER
#include "../IWorld.h"
#include "../../Reader.h"

class WorldDecorator abstract : public IWorld
{
public:
	WorldDecorator(IWorld* world);
	void Create() override;
protected:
	IWorld* mWorld;
};

#endif // !WORLDDECORATOR_HEADER
