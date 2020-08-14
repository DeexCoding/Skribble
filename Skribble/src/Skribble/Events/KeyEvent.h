#pragma once

#include "Event.h"

namespace Skribble
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeycode() const { return keycode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int _keycode) : keycode(_keycode) {}

		int keycode;
	};

	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int _keycode, int _repeatCount) : KeyEvent(_keycode), repeatCount(_repeatCount) {}

		int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent : " << keycode << " (" << repeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int repeatCount;
	};

	class KeyRelesedEvent : public KeyEvent
	{
	public:
		KeyRelesedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyRelesedEvent : " << keycode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};
}