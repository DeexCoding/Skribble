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

		const glm::vec3& GetPosition() const { return camera.GetPosition(); }
		void SetPosition(const glm::vec3& position) { camera.SetPosition(position); }

		const glm::vec3& GetRotation() const { return camera.GetRotation(); }
		void SetRotation(const glm::vec3& rotation) { camera.SetRotation(rotation); }

		float GetZoom() const { return zoom; }
		void SetZoom(float zoom) 
		{ 
			this->zoom = zoom; 
			camera.SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom); 
		}

	private:
		bool OnWindowResized(WindowResizeEvent& e);

		float aspectRatio;
		float zoom = 1.0f;
		bool rotation;

		Camera camera;
	};
}