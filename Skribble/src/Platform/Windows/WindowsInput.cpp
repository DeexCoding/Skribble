#include "skpch.h"
#include "Skribble/Core/Input.h"

#include "GLFW/glfw3.h"
#include "Skribble/Core/Application.h"

#ifdef SKRIBBLE_WINDOWS

namespace Skribble
{
	bool Input::GetKeyPress(const Key::KeyCode _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state =  glfwGetKey(window, _keycode);

		return state == GLFW_PRESS;
	}

	bool Input::GetKeyHold(const Key::KeyCode _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
	}

	bool Input::GetKeyUp(const Key::KeyCode _keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, _keycode);

		return state == GLFW_RELEASE;
	}

	bool Input::GetMouseButtonPress(const Key::MouseCode _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == GLFW_PRESS;
	}

	bool Input::GetMouseButtonHold(const Key::MouseCode _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return (state == GLFW_PRESS) || (state == GLFW_REPEAT);
	}
		
	bool Input::GetMouseButtonUp(const Key::MouseCode _button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, _button);

		return state == GLFW_RELEASE;
	}

	glm::vec2 Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double x, y;
		glfwGetCursorPos(window, &x, &y);

		return glm::vec2((float)x, (float)y);
	}
}

#endif