#pragma once
#ifndef SHADER_HEADER
#define SHADER_HEADER
#include "RendererDecorator.h"

class Shader final : public RendererDecorator
{
public:
	Shader(Renderer* renderer);
};

#endif // !SHADER_HEADER
