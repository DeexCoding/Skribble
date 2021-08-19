#include "skpch.h"

#include "OrthographicCameraController.h"

namespace Skribble
{
	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom), rotation(rotation)
	{

	}

	void OrthographicCameraController::Update()
	{

	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTFUNCTION(OrthographicCameraController::OnWindowResized));
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		camera.SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);

		return false;
	}
}