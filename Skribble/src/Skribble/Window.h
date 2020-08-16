#pragma once

#include "skpch.h"

#include "Skribble/Core.h"
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

		WindowPropeties(const std::string& _name = "Skribble", unsigned int _width = 640, unsigned int _height = 460)
			: name(_name), width(_width), height(_height) {}

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

		static Window* Create(const WindowPropeties& _propeties = WindowPropeties());
	};
}