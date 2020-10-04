#pragma once	
#ifndef IRENDERER_HEADER
#define IRENDERER_HEADER
#include "RenderExtension.h"

class IRenderer abstract
{
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
protected:	
	std::unique_ptr<IRenderExtension> mRenderExtension;
};

#endif // !IRENDERER_HEADER
