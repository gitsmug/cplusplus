#include "Camera.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

Camera::Camera() :
	viewDirection(0.0f, 0.0f, -1.0f),
	UP(0.0f, 1.0f, 0.0f)
{ }

mat4 Camera::GetWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, UP);
}