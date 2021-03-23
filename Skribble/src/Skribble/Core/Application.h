#pragma once

#include "Core.h"
#include "Core.h"
#include "../Events/Event.h"
#include "../Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"
#include "../Render/Shader.h"
#include "../Render/VertexBuffer.h"
#include "../Render/IndexBuffer.h"
#include "../Render/BufferLayout.h"
#include "../Render/VertexArray.h"
#include "Skribble/Render/Camera.h"

namespace Skribble
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void Quit();

		void OnEvent(Event& _event);

		void PushLayer(Layer* _layer);
		void PushOverlay(Layer* _layer);

		static Application& Get() { return *instance; }
		Window& GetWindow() { return *window; }

	private:
		static Application* instance;

		bool OnWindowClosed(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		bool minimized = false;
		bool running = false;
		std::unique_ptr<Window> window;
		LayerStack layerStack;

		float lastFrameTime = 0.0f;
	};

	//Define in CLIENT
	Application* CreateApplication();
}