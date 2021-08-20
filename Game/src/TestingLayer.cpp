#include "TestingLayer.h"

#include <glm/gtc/matrix_transform.hpp>

TestingLayer::TestingLayer() : Layer("Game"), camera(16.0f / 9.0f), playerPosition(0.0f), playerVelocity(0.0f)
{
	SKRIBBLE_PROFILE_SCOPE("GameLayer creation");

	shaders.Load("Texture", "assets/shaders/Texture.glsl");
	shaders.Load("Text", "assets/shaders/Text.glsl");
	Skribble::Batch2D::AddSamplers(shaders.Get("Texture"));
	Skribble::Batch2D::AddSamplers(shaders.Get("Text"));

	defaultTex = Skribble::Texture2D::Create("assets/textures/Default.png");

	camera.SetPosition({ 0.0f, 0.0f, -1.0f });
	camera.SetRotation({ 0.0f, 0.0f, 0.0f });
	camera.SetZoom(5.0f);
	comicSansFont = Skribble::Font::Create(16);
	comicSansFont->Load("assets/fonts/comic.ttf");

	listener = Skribble::CreateRef<Skribble::AudioListener>();
	listener->SetPosition({ 0.0f, 0.0f, 0.0f });
	listener->SetRotation({ 0.0f, 0.0f, 0.0f });

	sound = Skribble::AudioSource::LoadFromFile("assets/audio/supercoolbgmusic.wav");
	sound->SetLoop(true);
	sound->SetSpatial(true);
	sound->SetPosition({ 2.0f, 0.0f, 0.0f });
	Skribble::Audio::Play(sound);
}

void TestingLayer::Update()
{
	camera.Update();

	const float playerSpeed = 50.0f;
	const float playerGravity = 1.0f;
	const float playerJumpForce = 7.0f;
	float playerInput = 0.0f;

	if (Skribble::Input::GetKeyHold(Skribble::Key::LeftArrow))
	{
		playerInput = -1.0f;
	}
	else if (Skribble::Input::GetKeyHold(Skribble::Key::RightArrow))
	{
		playerInput = 1.0f;
	}
	else
	{
		playerInput = 0.0f;
	}

	if (Skribble::Input::GetKeyPress(Skribble::Key::UpArrow))
	{
		playerVelocity.y = playerJumpForce;
	}

	playerVelocity.x = playerInput * playerSpeed * Skribble::Time::elapsedSeconds;

	//playerVelocity.y -= playerGravity * Skribble::Time::elapsedSeconds;
	playerPosition += playerVelocity * Skribble::Time::elapsedSeconds;

	Skribble::Renderer::Clear(glm::vec4(0.1f, 0.05f, 0.2f, 1.0f));

	Skribble::Batch2D::Begin(camera.GetCamera(), shaders.Get("Texture"));
	Skribble::Batch2D::DrawQuad(playerPosition, -0.5f, 0.0f, glm::vec2(0.5f, 0.5f), Skribble::White,
		defaultTex, 1.0f, false, false);
	Skribble::Batch2D::End();

	Skribble::Batch2D::Begin(camera.GetCamera(), shaders.Get("Text"));
	Skribble::Batch2D::DrawText({ -8.5f, -4.0f }, 0.0f, 0.0f, { 0.05f, 0.05f }, Skribble::White, comicSansFont,
		"The quick brown fox jumps over the lazy dog");
	Skribble::Batch2D::End();
	
}

void TestingLayer::OnAttach()
{

}

void TestingLayer::OnDetach()
{
	
}

void TestingLayer::OnEvent(Skribble::Event& e)
{
	camera.OnEvent(e);

	Skribble::EventDispatcher _dispatcher(e);
	_dispatcher.Dispatch<Skribble::WindowResizeEvent>(BIND_EVENTFUNCTION(TestingLayer::OnWindowResize));
}

bool TestingLayer::OnWindowResize(Skribble::WindowResizeEvent& e)
{
	//float zoom = (float)e.GetWidth() / 1280.0f;
	
	//camera.SetZoom(zoom);
	
	return false;
}