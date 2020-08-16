#pragma once

#include "Core.h"

#include "glm/vec2.hpp"

namespace Skribble
{
	class Input
	{
	public:
		inline static bool SGetKeyPress(int _keycode) { return instance->GetKeyPress(_keycode); }
		inline static bool SGetKeyHold(int _keycode) { return instance->GetKeyHold(_keycode); }
		inline static bool SGetKeyUp(int _keycode) { return instance->GetKeyUp(_keycode); }

		inline static bool SGetMouseButtonPress(int _button) { return instance->GetMouseButtonPress(_button); }
		inline static bool SGetMouseButtonHold(int _button) { return instance->GetMouseButtonHold(_button); }
		inline static bool SGetMouseButtonUp(int _button) { return instance->GetMouseButtonUp(_button); }

		inline static glm::vec2 SGetMousePosition() { return instance->GetMousePosition(); }

	protected:
		virtual bool GetKeyPress(int _keycode) = 0;
		virtual bool GetKeyHold(int _keycode) = 0;
		virtual bool GetKeyUp(int _keycode) = 0;

		virtual bool GetMouseButtonPress(int _button) = 0;
		virtual bool GetMouseButtonHold(int _button) = 0;
		virtual bool GetMouseButtonUp(int _button) = 0;

		virtual glm::vec2 GetMousePosition() = 0;

	private:
		static Input* instance;
	
	};
}