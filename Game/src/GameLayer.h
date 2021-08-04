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
	FT_Library ft;

	Skribble::CameraController camera;
	Skribble::ShaderLibrary shaders;

	glm::vec2 playerPosition;
	glm::vec2 playerVelocity;

	Skribble::Ref<Skribble::Font> comicSansFont;
	Skribble::Ref<Skribble::Texture2D> defaultTex;
};