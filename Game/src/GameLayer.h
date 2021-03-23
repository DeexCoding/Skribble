#pragma once

#include "Skribble.h"

#include <vector>

class GameLayer : public Skribble::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void Update() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnEvent(Skribble::Event& _event) override;

	bool OnWindowResize(Skribble::WindowResizeEvent& e);

private:
	Skribble::CameraController camera;

	glm::vec3 cameraPosition;
	glm::vec3 squarePosition;
};