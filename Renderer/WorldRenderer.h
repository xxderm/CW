#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "Renderer.h"
#include "../World/World.h"

class WorldRenderer final : public Renderer
{
public:

private:
	World* mWorld;
};

#endif // !WORLDRENDERER_HEADER
