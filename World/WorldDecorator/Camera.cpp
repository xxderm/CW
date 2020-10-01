#include "Camera.h"

Camera::Camera(std::unique_ptr<IWorld> world)
	: 
	WorldDecorator{ std::move(world) },
	mPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	mUp(glm::vec3(0.0f, 1.0f, 0.0f)),
	mYaw(-90.),
	mPitch(0.),
	mFront(glm::vec3(0.0f, 0.0f, -1.0f)),
	mMovementSpeed(2.5),
	mMouseSensitivity(0.36),
	mZoom(45.)
{
	this->updateCameraVectors();
}

void Camera::Create()
{
	WorldDecorator::Create();
	// TODO: Init
}

const glm::vec3 Camera::getPosition()
{
	return mPosition;
}

const glm::mat4 Camera::getViewMatrix()
{
	return glm::lookAt(this->mPosition, this->mPosition + this->mFront, this->mUp);
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


