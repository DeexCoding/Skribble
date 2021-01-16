#pragma once

#include "Skribble.h"

class GameLayer : public Skribble::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void Update() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnEvent(Skribble::Event& _event) override;

private:
	Skribble::ShaderLibrary shaderLibrary;

	Skribble::Ref<Skribble::Shader> flatColorShader;
	Skribble::Ref<Skribble::VertexArray> vertexArray;
	Skribble::Ref<Skribble::Texture2D> gridTex;

	Skribble::Camera camera;

	glm::vec3 cameraPosition;
	glm::vec3 squarePosition;

};