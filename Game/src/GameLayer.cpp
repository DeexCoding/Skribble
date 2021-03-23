#include "GameLayer.h"

#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer() : Layer("Game"), camera(16.0f / 9.0f), squarePosition(0.0f)
{
	SKRIBBLE_PROFILE_SCOPE("GameLayer creation");
}

void GameLayer::Update()
{
	camera.Update();

	Skribble::Renderer::Clear(glm::vec4(0.1f, 0.05f, 0.2f, 1.0f));

	Skribble::Batch2D::Begin(camera.GetCamera());
	
	Skribble::Batch2D::DrawQuad({ 0.0f, 0.0f }, 0.0f, 45.0f, { 0.5f, 0.5f }, { 1.0f, 0.2f, 0.6f, 1.0f }, 
		nullptr, 1.0f);
	Skribble::Batch2D::DrawQuad({ 0.0f, 0.0f }, 0.1f, 45.0f, { 0.25f, 0.25f }, { 0.7f, 0.6f, 1.0f, 1.0f }, 
		nullptr, 1.0f);

	Skribble::Batch2D::End();
}

void GameLayer::OnAttach()
{

}

void GameLayer::OnDetach()
{

}

void GameLayer::OnEvent(Skribble::Event& e)
{
	camera.OnEvent(e);

	Skribble::EventDispatcher _dispatcher(e);
	_dispatcher.Dispatch<Skribble::WindowResizeEvent>(BIND_EVENTFUNCTION(GameLayer::OnWindowResize));
}

bool GameLayer::OnWindowResize(Skribble::WindowResizeEvent& e)
{
	//float zoom = (float)e.GetWidth() / 1280.0f;
	
	//camera.SetZoom(zoom);
	
	return false;
}