#pragma once
#ifndef WORLD_HEADER
#define WORLD_HEADER
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/matrix_transform_2d.hpp>
#include <glm/gtc/matrix_transform.inl>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/noise.hpp>
#include <time.h>
#include <glm/detail/_noise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

class World
{
public:

protected:
	glm::vec2 mScrSize;
	glm::vec2 mMapSize;
};

#endif // !WORLD_HEADER
