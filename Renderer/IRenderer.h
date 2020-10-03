#pragma once	
#ifndef IRENDERER_HEADER
#define IRENDERER_HEADER
#include "IRenderExtension.h"

class IRenderer abstract
{
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;
protected:	
};

#endif // !IRENDERER_HEADER
