#include "skpch.h"

#include "GLWindow.h"

#include "Skribble/Core/Core.h"

#include "Skribble/Events/ApplicationEvent.h"
#include "Skribble/Events/KeyEvent.h"
#include "Skribble/Events/MouseEvent.h"

#include "Platform/OpenGL/GLContext.h"

#include <GLAD/glad.h>

#ifdef SKRIBBLE_WINDOWS

//
namespace Skribble
{
	static bool glfwInitalized = false;

	static void GLFWError(int _error, const char* _description)
	{
		SKRIBBLE_CORE_ERROR("GLFW Error ({0}): {1}", _error, _description);
	}

	GLWindow::GLWindow(const WindowPropeties& propeties)
	{
		Initalize(propeties);
	}

	GLWindow::~GLWindow()
	{
		Shutdown();
	}

	void GLWindow::Initalize(const WindowPropeties& propeties)
	{
		SKRIBBLE_PROFILE_SCOPE("GLWindow::Initalize");

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

		context = new GLContext(window);
		context->Initalize();

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
				case GLFW_PRESS:
				{
					KeyPressedEvent _event(_key, 0);
					_data.callback(_event);
					break;
				}

				case GLFW_REPEAT:
				{
					//TODO : Extract repeat count
					KeyPressedEvent _event(_key, 1);
					_data.callback(_event);
					break;
				}

				case GLFW_RELEASE:
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
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent _event(_button);
					_data.callback(_event);
					break;
				}

				case GLFW_RELEASE:
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

				MouseMovedEvent _event((float)_x, (float)_y);
				_data.callback(_event);
			});


	}

	void GLWindow::Update()
	{
		SKRIBBLE_PROFILE_SCOPE("GLWindow::Update");

		glfwPollEvents();

		context->SwapBuffers();
	}

	void GLWindow::SetVSync(bool enabled)
	{
		SKRIBBLE_PROFILE_SCOPE("GLWindow::SetVSync");

		if (enabled) glfwSwapInterval(1);
		else glfwSwapInterval(0);

		data.vSync = enabled;
	}

	bool GLWindow::IsVSync() const
	{
		return data.vSync;
	}

	void GLWindow::Shutdown()
	{
		SKRIBBLE_PROFILE_SCOPE("GLWindow::Shutdown");

		glfwDestroyWindow(window);
	}
}

#endif