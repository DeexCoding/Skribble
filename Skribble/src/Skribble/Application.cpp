#include "skpch.h"
#include "Application.h"

#include "glm/glm.hpp"

#include "Skribble/Render/Renderer.h"

namespace Skribble
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		SKRIBBLE_CORE_ASSERT(!instance, "Application already exists!");

		instance = this;

		window = std::unique_ptr<Window>(Window::Create(WindowPropeties("Skribble", 800U, 450U)));
		window->SetEventCallback(BIND_EVENTFUNCTION(Application::OnEvent));

		vertexArray.reset(VertexArray::Create());

		float vertices[3 * 7] =
		{ 
			-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};

		Ref<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		
		BufferLayout layout =
		{
			{ ShaderDataType::Float3, "a_position" },
			{ ShaderDataType::Float4, "a_color" }
		};

		vertexBuffer->SetLayout(layout);

		vertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };

		Ref<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		vertexArray->SetIndexBuffer(indexBuffer);

		std::string vertexSrc = 
		R"(

#version 330 core

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec4 a_color;

out vec3 v_position;
out vec4 v_color;

void main()
{
v_position = a_position;
v_color = a_color;
gl_Position = vec4(a_position, 1.0f);
}

		)";

		std::string fragmentSrc =
			R"(

#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_position;
in vec4 v_color;

void main()
{
color = v_color;
}

		)";

		shader.reset(new Shader(vertexSrc, fragmentSrc));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		running = true;

		while (running)
		{
			RenderCommand::Clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

			Renderer::Begin();

			shader->Bind();
			Renderer::Submit(vertexArray);
			
			Renderer::End();
			
			for (Layer* layer : layerStack) layer->Update();

			window->Update();
		}
	}

	void Application::Quit()
	{
		running = false;
	}

	void Application::PushLayer(Layer* _layer)
	{
		layerStack.PushLayer(_layer);
	}

	void Application::PushOverlay(Layer* _layer)
	{
		layerStack.PushOverlay(_layer);
	}

	void Application::OnEvent(Event& _event)
	{
		EventDispatcher _dispatcher(_event);
		_dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENTFUNCTION(Application::OnWindowClosed));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(_event);
			if (_event.handled) break;
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& _event)
	{
		Application::Quit();
		return true;
	}
}