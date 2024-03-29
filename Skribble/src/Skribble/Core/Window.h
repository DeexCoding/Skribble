#pragma once

#include "skpch.h"

#include "Skribble/Core/Core.h"
#include "Skribble/Events/Event.h"

#include "glm/vec2.hpp"

namespace Skribble
{
	//Only for desktop systems

	struct WindowPropeties
	{
		std::string name;
		unsigned int width;
		unsigned int height;

		WindowPropeties(const std::string& name = "Skribble", unsigned int width = 640, unsigned int height = 460)
			: name(name), width(width), height(height) {}

	};

	class Window
	{
	public:
		using EventCallbackFunction = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void Update() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFunction& _callback) = 0;
		virtual void SetVSync(bool _enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Scope<Window> Create(const WindowPropeties& _propeties = WindowPropeties());
	};
}