#include "skpch.h"
#include "Application.h"

#include "glm/glm.hpp"

#include "Skribble/Render/Renderer.h"
#include "Skribble/Audio/Audio.h"

#include "Input.h"
#include "Time.h"

namespace Skribble
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		SKRIBBLE_PROFILE_SCOPE("Application::Application");

		SKRIBBLE_CORE_ASSERT(!instance, "Application already exists!");

		instance = this;

		window = std::unique_ptr<Window>(Window::Create(WindowPropeties("Skribble", 800U, 450U)));
		window->SetEventCallback(BIND_EVENTFUNCTION(Application::OnEvent));

		Renderer::Init();
		Audio::Initalize();
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		running = true;

		while (running)
		{
			Time::Calculate(lastFrameTime);
			lastFrameTime = Time::GetCurrentRealTime();

			if (!minimized)
			{
				for (Layer* layer : layerStack) layer->Update();
			}

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
		_dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENTFUNCTION(Application::OnWindowResize));

		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(_event);
			if (_event.handled) break;
		}
	}

	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		Application::Quit();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized = true;
			return false;
		}

		minimized = false;

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}
}