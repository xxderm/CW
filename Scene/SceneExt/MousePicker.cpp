#include "MousePicker.h"

MousePicker::MousePicker(std::unique_ptr<IWorld> world)
	: WorldDecorator{ std::move(world) }
{

}

void MousePicker::Create()
{
	WorldDecorator::Create();
	// TODO: Init
}

void MousePicker::setCamera(Camera* camera)
{
	this->mCamera = camera;
}

void MousePicker::setProjection(glm::mat4 projection)
{
	this->mProjectionMatrix = projection;
}

const glm::vec3 MousePicker::getCurrentTerrainPoint()
{
	return mCurrentTerrainPoint;
}

const glm::vec3 MousePicker::getCurrentRay()
{
	return mCurrentRay;
}

void MousePicker::Update(glm::mat4 view, Camera* camera)
{
	mCamera = camera;
	mViewMatrix = view;
	mCurrentRay = calculateMouseRay();
	if (intersectionInRange(0, mRayRange, mCurrentRay))
		mCurrentTerrainPoint = binarySearch(0, 0, mRayRange, mCurrentRay);
	else
		mCurrentTerrainPoint = glm::vec3(-1);
}

const glm::vec3 MousePicker::getPointOnRay(glm::vec3 ray, float distance)
{
	glm::vec3 camPos = mCamera->getPosition();
	glm::vec3 start = glm::vec3(camPos.x, camPos.y, camPos.z);
	glm::vec3 scaledRay = glm::vec3(ray.x * distance, ray.y * distance, ray.z * distance);
	return start + scaledRay;
}

const glm::vec3 MousePicker::binarySearch(int count, float start, float finish, glm::vec3 ray)
{
	float half = start + ((finish - start) / 2.f);
	if (count >= mRecCount)
	{
		glm::vec3 endPoint = getPointOnRay(ray, half);
		auto terrain = getTerrain(endPoint.x, endPoint.z);
		if (terrain)
		{
			return endPoint;
		}
		else
			return glm::vec3(-1);
	}
	if (intersectionInRange(start, half, ray))
	{
		return binarySearch(count + 1, start, half, ray);
	}
	else
		return binarySearch(count + 1, half, finish, ray);
}

const bool MousePicker::intersectionInRange(float start, float finish, glm::vec3 ray)
{
	glm::vec3 startPoint = getPointOnRay(ray, start);
	glm::vec3 endPoint = getPointOnRay(ray, finish);
	if (!isUnderGround(startPoint) && isUnderGround(endPoint))
		return true;
	else
		return false;
}

const bool MousePicker::isUnderGround(glm::vec3 testPoint)
{
	auto terrain = getTerrain(testPoint.x, testPoint.z);
	float height = 0;
	if (terrain)
	{
		height = getHeightOfTerrain(testPoint.x, testPoint.z);
	}
	if (testPoint.y < height)
		return true;
	else return false;
}

const bool MousePicker::getTerrain(float worldX, float worldZ)
{
	int x = worldX / (this->mMapSize.x);
	int z = worldZ / (this->mMapSize.x);
	if ((abs(floor(z) * (mMapSize.x))) + abs(floor(x)) < mTerrain.size()) return true;
	else return false;
}

const float MousePicker::getHeightOfTerrain(float x, float z)
{
	if ((abs(floor(z) * (mMapSize.x))) + abs(floor(x)) < mTerrain.size())
		return mTerrain.at((abs(floor(z) * (mMapSize.x))) + abs(floor(x))).y;
	else return -1;
}

const glm::vec3 MousePicker::calculateMouseRay()
{
	int mouseX;
	int mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	glm::vec2 normalizedCoords = getNormalizedDeviceCoords(mouseX, mouseY, this->mScrSize);
	glm::vec4 clipCoords = glm::vec4(normalizedCoords.x, normalizedCoords.y, -1.0f, 1.0f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);
	return worldRay;
}

const glm::vec3 MousePicker::toWorldCoords(glm::vec4 eyeCoords)
{
	glm::mat4 invertedView = glm::inverse(mViewMatrix);
	glm::vec4 rayWorld = invertedView * eyeCoords;
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	return glm::normalize(mouseRay);
}

const glm::vec4 MousePicker::toEyeCoords(glm::vec4 clipCoords)
{
	glm::mat4 invertedProjection = glm::inverse(mProjectionMatrix);
	glm::vec4 eyeCoords = invertedProjection * clipCoords;
	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

const glm::vec2 MousePicker::getNormalizedDeviceCoords(int mouseX, int mouseY, glm::vec2 ScrSize)
{
	float x = (2.0f * mouseX) / ScrSize.x - 1.f;
	float y = 1.f - (2.0f * mouseY) / ScrSize.y;
	return glm::vec2(x, y);
}

