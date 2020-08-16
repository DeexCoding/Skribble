#pragma once

#include "Skribble/Window.h"

#include <GLFW/glfw3.h>

namespace Skribble
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowPropeties& _propeties);
		virtual ~WindowsWindow();

		void Update() override;

		unsigned int GetWidth() const override { return data.width; }
		unsigned int GetHeight() const override { return data.height; }

		void SetEventCallback(const EventCallbackFunction& _callback) override { data.callback = _callback; }

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return window; }

	private:
		virtual void Initalize(const WindowPropeties& _propeties);
		virtual void Shutdown();

		GLFWwindow* window;

		struct WindowData
		{
			std::string title;
			unsigned width, height;
			bool vSync;

			EventCallbackFunction callback;
		};

		WindowData data;
	};
}