#pragma once

#include "Render/Camera.h"
#include "Time.h"
#include "Events/ApplicationEvent.h"
#include "Events/MouseEvent.h"

namespace Skribble
{
	class CameraController
	{
	public:
		CameraController(float aspectRatio, bool rotation = false);

		void Update();
		void OnEvent(Event& e);

		Camera& GetCamera() { return camera; }
		const Camera& GetCamera() const { return camera; }

		float GetZoom() { return zoom; }
		float SetZoom(float zoom) { this->zoom = zoom; }

		glm::vec3 cameraPosition = { 0.0f, 0.0f, 0.0f };

		float cameraRotation;

	private:
		bool OnWindowResized(WindowResizeEvent& e);

		float aspectRatio;
		float zoom = 1.0f;
		bool rotation;

		Camera camera;
	};
}