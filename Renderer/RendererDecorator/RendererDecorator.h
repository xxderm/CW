#pragma once
#ifndef RENDERER_DECORATOR_HEADER
#define RENDERER_DECORATOR_HEADER
#include "../Renderer.h"
#include "easylogging++.h"
#include "SDL.h"
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat2x2.hpp>


class RendererDecorator : public Renderer
{
public:
	RendererDecorator(Renderer* renderer);
protected:
	Renderer* mRenderer;
};

#endif // !RENDERERDECORATOR_HEADER
