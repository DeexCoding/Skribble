#pragma once

#include <glm/glm.hpp>

namespace Skribble
{
	class OrthographicCamera
	{
	public:
		OrthographicCamera(float _left, float _right, float _bottom, float _top);

		const glm::vec3& GetPosition() const { return position; }
		void SetPosition(const glm::vec3& _position) { position = _position; RecalculateView(); }

		const glm::vec3& GetRotation() const { return rotation; }
		void SetRotation(const glm::vec3& rotation) { this->rotation = rotation; RecalculateView(); }

		void SetProjection(float _left, float _right, float _bottom, float _top);

		const glm::mat4& GetProjectionMatrix() const { return projectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return viewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return viewProjectionMatrix; }

	private:
		void RecalculateView();

		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
		glm::mat4 viewProjectionMatrix;
		glm::vec3 position = { 0.0f, 0.0f, 0.0f };
		glm::vec3 rotation = { 0.0f, 0.0f, 0.0f };

	};
}