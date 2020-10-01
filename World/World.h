#pragma once
#ifndef WORLD_HEADER
#define WORLD_HEADER
#include "IWorld.h"

class World : public IWorld
{
public:
	void Create() override;
};

#endif


