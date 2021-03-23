#include "skpch.h"

#include "WindowsWindow.h"

#include "Skribble/Core/Core.h"

#include "Skribble/Events/ApplicationEvent.h"
#include "Skribble/Events/KeyEvent.h"
#include "Skribble/Events/MouseEvent.h"

#include "Platform/DirectX/DXContext.h"

#ifdef SKRIBBLE_WINDOWS

//
namespace Skribble
{
	static const std::string className = "WNDClassEx";

	LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch (message)
		{
		case WM_SIZE:
			//WindowData& data = *(WindowData*)GetWindowLongPtr(handle, GWLP_USERDATA);
			//RECT rect; 
			//GetWindowRect(handle, &rect);
			//data.width = rect.right;
			//data.height = rect.bottom;
			//
			//WindowResizeEvent _event(rect.right, rect.bottom);
			//data.callback(_event);

			break;

		case WM_CLOSE:
			//WindowCloseEvent event;
			break;

		case WM_KEYDOWN:
			break;

		case WM_KEYUP:
			break;

		case WM_LBUTTONDOWN:
			break;

		case WM_LBUTTONUP:
			break;

		case WM_RBUTTONDOWN:
			break;

		case WM_RBUTTONUP:
			break;

		case WM_MOUSEMOVE:
			const POINTS point = MAKEPOINTS(lParam);
			break;

		default:
			break;
		}

		return DefWindowProc(handle, message, wParam, lParam);
	}

	static void WindowsError(int _error, const char* _description)
	{
		SKRIBBLE_CORE_ERROR("GLFW Error ({0}): {1}", _error, _description);
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
		SKRIBBLE_PROFILE_SCOPE("WindowsWindow::Initalize");

		data.title = propeties.name;
		data.width = propeties.width;
		data.height = propeties.height;

		//Initalize

		WNDCLASSEX wndClass = { 0 };

		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_OWNDC;
		wndClass.lpfnWndProc = WndProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = GetModuleHandle(NULL); //Doesn't always work
		wndClass.hIcon = nullptr;
		wndClass.hCursor = nullptr;
		wndClass.hbrBackground = nullptr;
		wndClass.lpszMenuName = nullptr;
		wndClass.lpszClassName = (LPCWSTR)className.c_str(); // Shouldn't be a constant

		RegisterClassEx(&wndClass);

		//Create Window

		HWND hWnd = CreateWindowEx(0, (LPCWSTR)className.c_str(), (LPCWSTR)data.title.c_str(), 
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, 
			CW_USEDEFAULT, CW_USEDEFAULT, data.width, data.height, nullptr, nullptr, wndClass.hInstance, nullptr);

		SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)&data);

		window = &hWnd;

		ShowWindow(hWnd, SW_SHOW);

		context = new DXContext(window);
		context->Initalize();

		SetVSync(false); //TODO : Set it to an auctal vsync variable
	}

	void WindowsWindow::Update()
	{
		SKRIBBLE_PROFILE_SCOPE("WindowsWindow::Update");

		MSG msg;

		GetMessage(&msg, nullptr, 0, 0);
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		SKRIBBLE_PROFILE_SCOPE("WindowsWindow::SetVSync");

		data.vSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data.vSync;
	}

	void WindowsWindow::Shutdown()
	{

	}
}

#endif