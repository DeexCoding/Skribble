#pragma once

#include "Skribble/Input.h"

#include "glm/vec2.hpp"

namespace Skribble
{
	class WindowsInput : public Input
	{
	protected:
		virtual bool GetKeyPress(int _keycode) override;
		virtual bool GetKeyHold(int _keycode) override;
		virtual bool GetKeyUp(int _keycode) override;

		virtual bool GetMouseButtonPress(int _button) override;
		virtual bool GetMouseButtonHold(int _button) override;
		virtual bool GetMouseButtonUp(int _button) override;

		virtual glm::vec2 GetMousePosition() override;

	};
}