#pragma once
#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include "WorldDecorator.h"

enum Camera_Movement {
    CFORWARD,
    CBACKWARD,
    CLEFT,
    CRIGHT
};

class Camera final : public WorldDecorator
{
public:
	explicit Camera(std::unique_ptr<IWorld> world);
    void Create();
    const glm::vec3 getPosition();
    const glm::vec3 getFront();
    const glm::vec3 getUp();
    const glm::mat4 getViewMatrix();
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yoffset);
private:
    void updateCameraVectors();
private:   
    glm::vec3 mPosition;
    glm::vec3 mFront;
    glm::vec3 mUp;
    glm::vec3 mRight;
    glm::vec3 mWorldUp;
    float mYaw;
    float mPitch;
    float mMovementSpeed;
    float mMouseSensitivity;
    float mZoom;
};

#endif // !CAMERA_HEADER
