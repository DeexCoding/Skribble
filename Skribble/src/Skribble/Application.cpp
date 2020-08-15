#include "skpch.h"
#include "Application.h"

namespace Skribble
{
	Application* Application::instance = nullptr;

	Application::Application()
	{
		SKRIBBLE_CORE_ASSERT(!instance, "Application already exists!");

		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENTFUNCTION(Application::OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::Run()
	{
		running = true;

		while (running)
		{
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

		SKRIBBLE_CORE_TRACE("{0}", _event);

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