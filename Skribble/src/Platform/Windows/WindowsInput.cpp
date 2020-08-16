#include "skpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Skribble/Application.h"

namespace Skribble
{
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::GetKeyPress(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state =  glfwGetKey(window, _keycode);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::GetKeyHold(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return state == GLFW_REPEAT;
	}

	bool WindowsInput::GetKeyUp(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return state == GLFW_RELEASE;
	}

	bool WindowsInput::GetMouseButtonPress(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::GetMouseButtonHold(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == GLFW_REPEAT;
	}
		
	bool WindowsInput::GetMouseButtonUp(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == GLFW_RELEASE;
	}

	glm::vec2 WindowsInput::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return glm::vec2((float)x, (float)y);
	}
}