#pragma once
#ifndef WORLD_RENDERER_HEADER
#define WORLD_RENDERER_HEADER
#include "IRenderer.h"

class WorldRenderer final : public IRenderer
{
public:
	void Render() override;
	void Update() override;
	void Init() override;
private:
};

#endif // !WORLDRENDERER_HEADER
