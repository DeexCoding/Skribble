#pragma once

#include "Keycode.h"
#include "Mousecode.h"

#include "glm/vec2.hpp"

namespace Skribble
{
	class Input
	{
	public:
		static bool GetKeyPress(const Key::KeyCode _keycode);
		static bool GetKeyHold(const Key::KeyCode _keycode);
		static bool GetKeyUp(const Key::KeyCode _keycode);

		static bool GetMouseButtonPress(const Key::MouseCode _button);
		static bool GetMouseButtonHold(const Key::MouseCode _button);
		static bool GetMouseButtonUp(const Key::MouseCode _button);

		static glm::vec2 GetMousePosition();
	};
}