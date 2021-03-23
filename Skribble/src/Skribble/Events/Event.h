#pragma once

#include "skpch.h"

#include "Skribble/Core/Core.h"

namespace Skribble
{
	//Currently events block the entire program. Definietly will change in the future.

	//TODO: Make events much simpler : Not make them entire classes, maybe make them just functions or lambdas

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMove,
		AppTick, AppUpdate, AppDraw,
		KeyPressed, KeyRelesed,
		MouseButtonPressed, MouseButtonRelesed, MouseMoved, MouseScrolled
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BSR(0),
		EventCategoryInput       = BSR(1),
		EventCategoryKeyboard    = BSR(2),
		EventCategoryMouse       = BSR(3),
		EventCategoryMouseButton = BSR(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class Event
	{
	public:
		bool handled = false;

		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& _event) : m_Event(_event) {}

		template<typename T, typename F>
		bool Dispatch(const F& _function)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.handled = _function(static_cast<T&>(m_Event));
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}
}