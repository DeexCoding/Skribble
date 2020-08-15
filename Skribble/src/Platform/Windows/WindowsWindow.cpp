#include "skpch.h"

#include "WindowsWindow.h"

#include "Skribble/Core.h"

#include "Skribble/Events/ApplicationEvent.h"
#include "Skribble/Events/KeyEvent.h"
#include "Skribble/Events/MouseEvent.h"

#include <GLAD/glad.h>

namespace Skribble
{
	static bool glfwInitalized = false;

	static void GLFWError(int _error, const char* _description)
	{
		SKRIBBLE_CORE_ERROR("GLFW Error ({0}): {1}", _error, _description);
	}

	Window* Window::Create(const WindowPropeties& propeties)
	{
		return new WindowsWindow(propeties);
	}

	WindowsWindow::WindowsWindow(const WindowPropeties& propeties)
	{
		Initalize(propeties);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Initalize(const WindowPropeties& propeties)
	{
		data.title = propeties.name;
		data.width = propeties.width;
		data.height = propeties.height;

		if (!glfwInitalized)
		{
			int success = glfwInit();
			SKRIBBLE_CORE_ASSERT(success, "Couldn't initalize GLFW!");

			glfwSetErrorCallback(GLFWError);

			glfwInitalized = true;
		}

		window = glfwCreateWindow((int)propeties.width, (int)propeties.height, data.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		int glad = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		SKRIBBLE_CORE_ASSERT(status, "Couldn't initalize GLAD!");
		glfwSetWindowUserPointer(window, &data);
		SetVSync(false); //TODO : Set it to an auctal vsync variable


		glfwSetWindowSizeCallback(window, [](GLFWwindow* _window, int _width, int _height)
			{
				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);
				_data.width = _width;
				_data.height = _height;

				WindowResizeEvent _event(_width, _height);
				_data.callback(_event);
			});

		glfwSetWindowCloseCallback(window, [](GLFWwindow* _window)
			{
				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);
				
				WindowCloseEvent _event;
				_data.callback(_event);
			});

		glfwSetKeyCallback(window, [](GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) 
			{
				//TODO : Convert to skribble keycodes

				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);

				switch (_action)
				{
					case SKRIBBLE_PRESS:
					{
						KeyPressedEvent _event(_key, 0);
						_data.callback(_event);
						break;
					}

					case SKRIBBLE_REPEAT:
					{
						//TODO : Extract repeat count
						KeyPressedEvent _event(_key, 1);
						_data.callback(_event);
						break;
					}

					case SKRIBBLE_RELEASE:
					{
						KeyRelesedEvent _event(_key);
						_data.callback(_event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(window, [](GLFWwindow* _window, int _button, int _action, int _mods)
			{
				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);

				switch (_action)
				{
					case SKRIBBLE_PRESS:
					{
						MouseButtonPressedEvent _event(_button);
						_data.callback(_event);
						break;
					}

					case SKRIBBLE_RELEASE:
					{
						MouseButtonRelesedEvent _event(_button);
						_data.callback(_event);
						break;
					}
				}
			});


		glfwSetScrollCallback(window, [](GLFWwindow* _window, double _x, double _y) 
			{
				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);

				MouseScrolledEvent _event((float)_x, (float)_y);
				_data.callback(_event);
			});

		glfwSetCursorPosCallback(window, [](GLFWwindow* _window, double _x, double _y) 
			{
				WindowData& _data = *(WindowData*)glfwGetWindowUserPointer(_window);

				MouseMovedEvent _event((float) _x, (float)_y);
				_data.callback(_event);
			});


	}

	void WindowsWindow::Update()
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.vSync;
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(window);
	}
}