#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "Renderer.h"
#include "../World/IWorld.h"

class WorldRenderer final : public Renderer
{
public:
	void Render() override;
private:
};

#endif // !WORLDRENDERER_HEADER
