#pragma once

#include "Skribble/Core/Window.h"
#include "Skribble/Render/GraphicsContext.h"

#ifdef SKRIBBLE_WINDOWS

#include <GLFW/glfw3.h>

namespace Skribble
{
	class GLWindow : public Window
	{
	public:
		GLWindow(const WindowPropeties& _propeties);
		virtual ~GLWindow();

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

		Scope<GrphicsContext> context;

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

#endif