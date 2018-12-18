#pragma once

#include <glm/glm.hpp>
using glm::mat4;
using glm::vec2;
using glm::vec3;

class Camera
{
private:
	vec3 position;
	vec3 viewDirection;
	const vec3 UP;
	vec2 oldMousePosition;

public:
	Camera();
	void MouseUpdate(const vec2& newMousePosition);
	mat4 GetWorldToViewMatrix() const;
};