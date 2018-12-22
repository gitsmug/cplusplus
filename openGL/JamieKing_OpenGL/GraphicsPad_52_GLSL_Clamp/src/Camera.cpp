#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
using glm::mat3;

const float Camera::MOVEMENT_SPEED = 0.1f;

Camera::Camera() :
	//position(0.0f, 0.0f, 0.0f),
	position(3.11094999f, 2.23070025f, 2.86016989f),
	//position(0.201957405f, 3.63646984f, 4.53021145f),
	//viewDirection(0.0f, 0.0f, -1.0f),
	//viewDirection(-0.0672515184f, -0.636077762f, -0.768687665f),
	viewDirection(-0.663740635f, -0.492421985f, -0.562995136f),

	UP(0.0f, 1.0f, 0.0f),
	oldMousePosition(0.0f, 0.0f)
{ }

void Camera::MouseUpdate(const vec2& newMousePosition)
{
	vec2 mouseDelta = newMousePosition - oldMousePosition;

	// Mouse jumpyness shit.
	if (glm::length(mouseDelta) < glm::radians(50.0f))
	{
		const float SCALE_SPEED = 0.5f;
		strafeDirection = glm::cross(viewDirection, UP);
		mat4 rotator = glm::rotate(-mouseDelta.x * SCALE_SPEED, UP)
			* glm::rotate(-mouseDelta.y * SCALE_SPEED, strafeDirection);

		viewDirection = mat3(rotator) * viewDirection;
	}

	oldMousePosition = newMousePosition;
}

mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::StrafeRight()
{
	position += MOVEMENT_SPEED * strafeDirection;
}

void Camera::StrafeLeft()
{
	position += -MOVEMENT_SPEED * strafeDirection;
}

void Camera::MoveDown()
{
	position += -MOVEMENT_SPEED * UP;
}

void Camera::MoveUp()
{
	position += MOVEMENT_SPEED * UP;
}

void Camera::MoveBackward()
{
	position -= MOVEMENT_SPEED * viewDirection;
}

void Camera::MoveForward()
{
	position += MOVEMENT_SPEED * viewDirection;
}