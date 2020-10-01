#pragma once	
#ifndef RENDERER_HEADER
#define RENDERER_HEADER
#include "easylogging++.h"
#include "SDL.h"
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>

class Renderer abstract
{
public:
	virtual void Init() = 0;
	virtual void Render() = 0;
};

#endif // !RENDERER_HEADER
