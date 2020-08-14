#pragma once

#include "Event.h"

namespace Skribble
{
	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int _width, unsigned int _height) : width(_width), height(_height) {} //Might not work
		
		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }
		
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent : " << width << ", " << height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int width, height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class AppDrawEvent : public Event
	{
	public:
		AppDrawEvent() = default;

		EVENT_CLASS_TYPE(AppDraw)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}