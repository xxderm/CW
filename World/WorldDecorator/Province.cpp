#include "Province.h"

namespace glm
{
	bool operator<(const glm::vec3& lhs, const glm::vec3& rhs)
	{
		return lhs.x < rhs.x ||
			lhs.x == rhs.x && (lhs.y < rhs.y || lhs.y == rhs.y && lhs.z < rhs.z);
	}
}

Province::Province(IWorld* world)
	: WorldDecorator(world)
{	
}

void Province::Create()
{
	this->Init();
	WorldDecorator::Create();
}

void Province::Init()
{
	std::ifstream provStream("Resources/definition.csv");
	if (!provStream.is_open())
	{
		LOG(ERROR) << "Failed to open province definition file";
		throw std::exception();
	}
	std::string line;
	for (int i = 0; std::getline(provStream, line); i++)
	{
		typedef std::vector<std::string> spt;
		spt split_vec;
		boost::split(split_vec, line, boost::is_any_of(";"));

		ProvinceFormat province;
		province.Color = glm::vec3(
			std::stoi(split_vec.at(1)),
			std::stoi(split_vec.at(2)),
			std::stoi(split_vec.at(3))
		);
		province.Id = std::stoi(split_vec.at(0));
		province.Type = split_vec.at(4);
		province.Coastal = split_vec.at(5);
		province.Terrain = split_vec.at(6);
		province.Continent = std::stoi(split_vec.at(7));
		mProvinces.push_back(province);
		mProvinceColorMap.try_emplace(province.Color, province);
	}
	provStream.close();
}

const ProvinceFormat& Province::getProvince(int Id)
{
	return mProvinces.at(Id);
}

const ProvinceFormat& Province::getProvince(glm::vec3 Color)
{
	if (mProvinceColorMap.count(Color) > 0)
		return mProvinceColorMap.at(Color);
	LOG(ERROR) << "Province not found";
	throw std::exception();
}

void Province::setProvince(int Id, ProvinceFormat provice)
{
	mProvinces.at(Id) = provice;
}

