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
#include <boost/thread.hpp>
#include <string>
#include "easylogging++.h"
#include "WorldExt/Country.h"
#include "WorldExt/Province.h"
#include "WorldExt/State.h"
#include <boost/thread.hpp>

class World final 
{
public:
	World();
	void Create();
	Country* getCountries();
	Province* getProvinces();
	State* getStates();
private:
	Country* mCountry;
	Province* mProvince;
	State* mState;
};

#endif


