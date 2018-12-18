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
	viewDirection = mat3(glm::rotate(-mouseDelta.x, UP)) * viewDirection;
	oldMousePosition = newMousePosition;
}

mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}