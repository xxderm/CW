#pragma once
#ifndef INTERFACE_WORLD_HEADER
#define INTERFACE_WORLD_HEADER
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
#include <boost/thread.hpp>
#include <string>
#include "easylogging++.h"

class IWorld abstract
{
public:
	virtual void Create() = 0;
protected:
	glm::vec2 mScrSize;
	glm::vec2 mMapSize;
};

#endif // !WORLD_HEADER
