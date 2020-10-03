#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "Renderer.h"
#include "../World/IWorld.h"

class WorldRenderer final : public Renderer
{
public:
	void Render() override;
	void Update() override;
	void Init() override;
protected:
	void Use(const char* Name) override;
private:
};

#endif // !WORLDRENDERER_HEADER
