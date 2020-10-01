#pragma once
#ifndef WORLD_DECORATOR_HEADER
#define WORLD_DECORATOR_HEADER
#include "../IWorld.h"
#include "../../Reader.h"

class WorldDecorator abstract : public IWorld
{
public:
	WorldDecorator(std::unique_ptr<IWorld> world);
	void Create() override;
protected:
	std::unique_ptr<IWorld> mWorld;
};

#endif // !WORLDDECORATOR_HEADER
