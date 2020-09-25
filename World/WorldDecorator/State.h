#pragma once
#ifndef STATE_HEADER
#define STATE_HEADER
#include "WorldDecorator.h"

class State final : public WorldDecorator
{
public:
	State(World* world);
};

#endif // !STATE_HEADER
