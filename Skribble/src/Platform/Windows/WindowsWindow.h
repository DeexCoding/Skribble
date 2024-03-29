#pragma once

#include "Skribble/Core/Window.h"
#include "Skribble/Render/GraphicsContext.h"

#ifdef SKRIBBLE_WINDOWS

#include <Windows.h>

namespace Skribble
{
	struct WindowData
	{
		std::string title;
		unsigned width, height;
		bool vSync;

		Window::EventCallbackFunction callback;
	};

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

		HWND* window;

		GrphicsContext* context;

		WindowData data;
	};
}

#endif