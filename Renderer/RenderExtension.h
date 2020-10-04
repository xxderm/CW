#pragma once
#ifndef RENDERER_EXTENSION_HEADER
#define RENDERER_EXTENSION_HEADER
#include "IRenderExtension.h"

class RenderExtension final : public IRenderExtension
{
public:
	void Create() override;
};

#endif // !RENDERER_EXTENSION_HEADER
