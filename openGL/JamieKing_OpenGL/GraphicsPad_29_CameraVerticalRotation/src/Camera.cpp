#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
using glm::mat3;

Camera::Camera() :
	viewDirection(0.0f, 0.0f, -1.0f),
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
		vec3 toRotateAround = glm::cross(viewDirection, UP);
		mat4 rotator = glm::rotate(-mouseDelta.x * SCALE_SPEED, UP)
			* glm::rotate(-mouseDelta.y * SCALE_SPEED, toRotateAround);

		viewDirection = mat3(rotator) * viewDirection;
	}

	oldMousePosition = newMousePosition;
}

mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}