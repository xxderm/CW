#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 mwu, glm::vec3 mf)
	: 
	mPosition(position),
	mWorldUp(mwu),
	mYaw(-90.),
	mPitch(0.),
	mFront(mf),
	mMovementSpeed(2.5),
	mMouseSensitivity(0.36),
	mZoom(45.)
{
	this->updateCameraVectors();
}

glm::vec3 Camera::getPosition()
{
	return mPosition;
}

const glm::vec3 Camera::getFront()
{
	return mFront;
}

const glm::vec3 Camera::getUp()
{
	return mUp;
}

const glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->mPosition, this->mPosition + this->mFront, this->mUp);
}

const glm::vec3 Camera::getWorldUp()
{
	return mWorldUp;
}

const glm::vec3 Camera::getRight()
{
	return mRight;
}

void Camera::setUp(glm::vec3 up)
{
	this->mUp = up;
}

void Camera::setRight(glm::vec3 r)
{
	mRight = r;
}

void Camera::setFront(glm::vec3 f)
{
	this->mFront = f;
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = this->mMovementSpeed * deltaTime;
	if (direction == CFORWARD)
		this->mPosition += this->mFront * velocity;
	if (direction == CBACKWARD)
		this->mPosition -= this->mFront * velocity;
	if (direction == CLEFT)
		this->mPosition -= this->mRight * velocity;
	if (direction == CRIGHT)
		this->mPosition += this->mRight * velocity;
	if (direction == ZTOP)
		this->mPosition.z -= 1 * velocity;
	if (direction == ZBOTTOM)
		this->mPosition.z += 1 * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
	xoffset *= this->mMouseSensitivity;
	yoffset *= this->mMouseSensitivity;

	this->mYaw += xoffset;
	this->mPitch += yoffset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (constrainPitch)
	{
		if (this->mPitch > 89.0f)
			this->mPitch = 89.0f;
		if (this->mPitch < -89.0f)
			this->mPitch = -89.0f;
	}

	// Update Front, Right and Up Vectors using the updated Eular angles
	this->updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset)
{
	if (this->mZoom >= 1.0f && this->mZoom <= 45.0f)
		this->mZoom -= yoffset;
	if (this->mZoom <= 1.0f)
		this->mZoom = 1.0f;
	if (this->mZoom >= 45.0f)
		this->mZoom = 45.0f;
}

void Camera::updateCameraVectors()
{
	glm::vec3 front;
	front.x = cos(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
	front.y = sin(glm::radians(this->mPitch));
	front.z = sin(glm::radians(this->mYaw)) * cos(glm::radians(this->mPitch));
	this->mFront = glm::normalize(front);
	this->mRight = glm::normalize(glm::cross(this->mFront, this->mWorldUp)); 
	this->mUp = glm::normalize(glm::cross(this->mRight, this->mFront));
}


