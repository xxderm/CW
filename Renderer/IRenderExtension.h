#pragma once
#ifndef IRENDERER_EXTENSION_HEADER
#define IRENDERER_EXTENSION_HEADER
#include "easylogging++.h"
#include "SDL.h"
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>
#include <memory>

class IRenderExtension abstract
{
public:
	virtual void Create() = 0;
};

#endif // !IRENDERER_EXTENSION_HEADER
