#pragma once
#ifndef PROVINCE_HEADER
#define PROVINCE_HEADER
#include "WorldDecorator.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
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
};

class Province final : public WorldDecorator
{
public:
	Province(World* world);
	void Init();
	const ProvinceFormat& getProvince(int Id);
	const ProvinceFormat& getProvince(glm::vec3 Color);
	void setProvince(int Id, ProvinceFormat provice);
private:
	std::vector<ProvinceFormat> mProvinces;
	std::map<glm::vec3, ProvinceFormat> mProvinceColorMap;

};

#endif // !PROVINCE_HEADER