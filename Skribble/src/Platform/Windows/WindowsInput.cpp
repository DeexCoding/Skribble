#include "skpch.h"
#include "WindowsInput.h"

#include "GLFW/glfw3.h"
#include "Skribble/Application.h"

//
namespace Skribble
{
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::GetKeyPress(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state =  glfwGetKey(window, _keycode);

		return state == SKRIBBLE_PRESS;
	}

	bool WindowsInput::GetKeyHold(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return state == SKRIBBLE_REPEAT;
	}

	bool WindowsInput::GetKeyUp(int _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return state == SKRIBBLE_RELEASE;
	}

	bool WindowsInput::GetMouseButtonPress(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == SKRIBBLE_PRESS;
	}

	bool WindowsInput::GetMouseButtonHold(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == SKRIBBLE_REPEAT;
	}
		
	bool WindowsInput::GetMouseButtonUp(int _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == SKRIBBLE_RELEASE;
	}

	//TODO: Return mouse position as a float2
	float WindowsInput::GetMouseX()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return x;
	}

	float WindowsInput::GetMouseY()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return y;
	}
}