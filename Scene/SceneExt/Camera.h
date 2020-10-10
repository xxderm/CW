#pragma once
#ifndef CAMERA_HEADER
#define CAMERA_HEADER
#include <list>
#include <SDL.h>
#include <GL/glew.h>
#include "GL/GL/GL.H"
#include "GL/GL/GLU.H"
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
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <boost/thread.hpp>
#include <string>
#include "easylogging++.h"

enum Camera_Movement {
    CFORWARD,
    CBACKWARD,
    CLEFT,
    CRIGHT
};

class Camera final 
{
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f));
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
