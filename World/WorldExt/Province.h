#pragma once
#ifndef PROVINCE_HEADER
#define PROVINCE_HEADER
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <glm/vec3.hpp>
#include <map>
#include "easylogging++.h"
#include <fstream>
#include <vector>

struct ProvinceFormat
{
	std::string Type;
	std::string Terrain;
	std::string Coastal;
	glm::vec3 Color;
	glm::vec3 Position;
	unsigned int StateId;
	unsigned int Id;
	unsigned int Continent;

	enum TYPE
	{
		IRON,
		OIL,
		RUBBER,
		WOOD,
		GOLD,
		CORN,
		MAX
	};
	int Resource[MAX]{ 0 };

};

class Province final
{
public:
	Province();
	const ProvinceFormat& getProvince(int Id);
	const ProvinceFormat& getProvince(glm::vec3 Color);
	void setProvince(int Id, ProvinceFormat provice);
	void Init();
private:
	std::vector<ProvinceFormat> mProvinces;
	std::map<glm::vec3, ProvinceFormat> mProvinceColorMap;

};

#endif // !PROVINCE_HEADER