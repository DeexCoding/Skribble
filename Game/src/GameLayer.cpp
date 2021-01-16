#include "GameLayer.h"

#include <glm/gtc/matrix_transform.hpp>

GameLayer::GameLayer() : Layer("Game"), camera(-1.6f, 1.6f, -0.9f, 0.9f), cameraPosition(0.0f), 
	squarePosition(0.0f)
{
	vertexArray.reset(Skribble::VertexArray::Create());

	float vertices[5 * 4] =
	{
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f
	};

	Skribble::Ref<Skribble::VertexBuffer> vertexBuffer;
	vertexBuffer.reset(Skribble::VertexBuffer::Create(vertices, sizeof(vertices)));

	Skribble::BufferLayout layout =
	{
		{ Skribble::ShaderDataType::Float3, "a_position" },
		{ Skribble::ShaderDataType::Float2, "a_texCoord" },
	};

	vertexBuffer->SetLayout(layout);

	vertexArray->AddVertexBuffer(vertexBuffer);

	uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };

	Skribble::Ref<Skribble::IndexBuffer> indexBuffer;
	indexBuffer.reset(Skribble::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

	vertexArray->SetIndexBuffer(indexBuffer);

	std::string flatColorVertexSrc =
		R"(

#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_viewProjection;
uniform mat4 u_transform;

void main()
{
gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0f);
}

		)";

	std::string flatColorFragmentSrc =
		R"(

#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_color;

void main()
{
color = u_color;
}

		)";

	flatColorShader = Skribble::Shader::Create("FlatColor", flatColorVertexSrc, flatColorFragmentSrc);

	shaderLibrary.Load("assets/shaders/Texture.glsl");

	gridTex = Skribble::Texture2D::Create("assets/textures/512X512 orange grid.png");

	shaderLibrary.Get("Texture")->Bind();
	shaderLibrary.Get("Texture")->SetInt("u_texture", 0);
}

void GameLayer::Update()
{
	const float playerSpeed = 3.0f;

	if (Skribble::Input::GetKeyHold(Skribble::Key::LeftArrow))
	{
		squarePosition.x -= playerSpeed * Skribble::Time::elapsedSeconds;
	}
	else if (Skribble::Input::GetKeyHold(Skribble::Key::RightArrow))
	{
		squarePosition.x += playerSpeed * Skribble::Time::elapsedSeconds;
	}
	else
	{

	}

	if (Skribble::Input::GetKeyHold(Skribble::Key::DownArrow))
	{
		squarePosition.y -= playerSpeed * Skribble::Time::elapsedSeconds;
	}
	else if (Skribble::Input::GetKeyHold(Skribble::Key::UpArrow))
	{
		squarePosition.y += playerSpeed * Skribble::Time::elapsedSeconds;
	}
	else
	{

	}

	camera.SetPosition(cameraPosition);

	Skribble::Renderer::Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	Skribble::Renderer::Begin(camera);

	glm::vec4 color(0.0f, 0.0f, 1.0f, 1.0f);

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), squarePosition) * scale;

	gridTex->Bind();

	Skribble::Renderer::Submit(vertexArray, shaderLibrary.Get("Texture"), transform);

	Skribble::Renderer::End();
}

void GameLayer::OnAttach()
{

}

void GameLayer::OnDetach()
{

}

void GameLayer::OnEvent(Skribble::Event& _event)
{

}