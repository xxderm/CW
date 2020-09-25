#pragma once
#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER
#include "RendererDecorator.h"

class Texture final : public RendererDecorator
{
public:
	Texture(Renderer* renderer);
};

#endif // !TEXTURE_HEADER
