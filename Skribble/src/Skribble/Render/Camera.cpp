#include "skpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Skribble
{
	Camera::Camera(float _left, float _right, float _bottom, float _top) : 
		projectionMatrix(glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f)), viewMatrix(1.0f)
	{
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void Camera::RecalculateView()
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 
			glm::radians(rotation), glm::vec3(0, 0, 1));

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}