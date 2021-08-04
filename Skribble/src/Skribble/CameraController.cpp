#include "skpch.h"

#include "CameraController.h"

namespace Skribble
{
	CameraController::CameraController(float aspectRatio, bool rotation)
		: aspectRatio(aspectRatio), camera(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom), rotation(rotation)
	{

	}

	void CameraController::Update()
	{

	}

	void CameraController::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);

		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTFUNCTION(CameraController::OnWindowResized));
	}

	bool CameraController::OnWindowResized(WindowResizeEvent& e)
	{
		aspectRatio = (float)e.GetWidth() / (float)e.GetHeight();
		camera.SetProjection(-aspectRatio * zoom, aspectRatio * zoom, -zoom, zoom);

		return false;
	}
}