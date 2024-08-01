#include "Window.h"

#include <string>


Window* window = nullptr;

Window::Window()
{
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event fired when the window is created
		window->onCreate();
		break;
	}

	case WM_DESTROY:
	{
		// Event fired when the window is destroyed
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}


bool Window::init()
{
	// Window definition
	WNDCLASSEX wc;

	// Window properties
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = NULL;
	wc.lpszClassName = L"MyWindowClass";
	wc.lpszMenuName = L"";
	wc.style = NULL;
	wc.lpfnWndProc = WndProc;

	if (!::RegisterClassEx(&wc)) // Fail safe if the registration of the class fails return false
		return false;

	m_hwnd=::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, L"MyWindowClass", L"DirectX Application", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	// Show the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	if (!window)
		window = this;

	return true;
}

bool Window::release()
{
	// Destroy the window
	if (!::DestroyWindow(m_hwnd))
		return false;

	return true;
}

Window::~Window()
{
}
