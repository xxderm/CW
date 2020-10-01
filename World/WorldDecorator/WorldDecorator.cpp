#include "WorldDecorator.h"

WorldDecorator::WorldDecorator(IWorld* world)
	: mWorld(world)
{
}

void WorldDecorator::Create()
{
	mWorld->Create();
}
