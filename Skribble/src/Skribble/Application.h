#pragma once

#include "Core.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Skribble/LayerStack.h"

namespace Skribble
{
	class SKRIBBLE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

		void OnEvent(Event& _event);

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _layer);

	private:
		bool OnWindowClosed(WindowCloseEvent& _event);

		bool running = false;
		std::unique_ptr<Window> window;
		LayerStack layerStack;
	};

	//Define in CLIENT
	Application* CreateApplication();
}