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
		glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), { 1, 0, 0 }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), { 0, 1, 0 }) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), { 0, 0, 1 });

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * rotationMatrix;

		viewMatrix = glm::inverse(transform);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}

	void Camera::SetProjection(float _left, float _right, float _bottom, float _top)
	{
		projectionMatrix = glm::ortho(_left, _right, _bottom, _top, -1.0f, 1.0f);
		viewProjectionMatrix = projectionMatrix * viewMatrix;
	}
}