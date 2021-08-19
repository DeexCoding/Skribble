#pragma once

#include "Skribble.h"

#include <vector>

class TestingLayer : public Skribble::Layer
{
public:
	TestingLayer();
	virtual ~TestingLayer() = default;

	void Update() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnEvent(Skribble::Event& _event) override;

	bool OnWindowResize(Skribble::WindowResizeEvent& e);

	Skribble::OrthographicCameraController camera;
	Skribble::ShaderLibrary shaders;

	glm::vec2 playerPosition;
	glm::vec2 playerVelocity;

	Skribble::Ref<Skribble::Font> comicSansFont;
	Skribble::Ref<Skribble::Texture2D> defaultTex;

	Skribble::Ref<Skribble::AudioListener> listener;

	Skribble::Ref<Skribble::AudioSource> sound;
};