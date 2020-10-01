#include "WorldDecorator.h"

WorldDecorator::WorldDecorator(std::unique_ptr<IWorld> world)
	: mWorld{ std::move(world) }
{
}

void WorldDecorator::Create()
{
	mWorld->Create();
}
