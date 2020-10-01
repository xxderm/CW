#pragma once
#ifndef MOUSE_PICKER_HEADER
#define MOUSE_PICKER_HEADER
#include "WorldDecorator.h"
#include "Camera.h"
#include <SDL.h>
#include <vector>

class MousePicker final : public WorldDecorator
{
public:
    MousePicker(std::unique_ptr<IWorld> world);
    void Create() override;
    void setCamera(Camera* camera);
    void setProjection(glm::mat4 projection);
    const glm::vec3 getCurrentTerrainPoint();
    const glm::vec3 getCurrentRay();
    const glm::vec3 getPointOnRay(glm::vec3 ray, float distance);
    const glm::vec3 binarySearch(int count, float start, float finish, glm::vec3 ray);
    const static glm::vec2 getNormalizedDeviceCoords(int mouseX, int mouseY, glm::vec2 ScrSize);
    void Update(glm::mat4 view, Camera* camera);
private:
    const bool intersectionInRange(float start, float finish, glm::vec3 ray);
    const bool isUnderGround(glm::vec3 testPoint);
    const bool getTerrain(float worldX, float worldZ);
    const float getHeightOfTerrain(float x, float z);
    const glm::vec3 calculateMouseRay();
    const glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
    const glm::vec4 toEyeCoords(glm::vec4 clipCoords);

private:
    glm::vec3 mCurrentRay;
    glm::mat4 mProjectionMatrix;
    glm::mat4 mViewMatrix;
    Camera* mCamera;
    std::vector<glm::vec3> mTerrain;
    glm::vec3 mCurrentTerrainPoint;
    int mRecCount = 200;
    float mRayRange = 600;
};

#endif // !MOUSE_PICKER_HEADER
