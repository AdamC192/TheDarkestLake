#pragma once
#include <Windows.h>

class Window
{
public:
	Window();

	// Create the window
	bool init();
	bool broadcast();

	// Release the window
	bool release();

	// Events
	virtual void onCreate()=0;
	virtual void onUpdate()=0;
	virtual void onDestroy()=0;

	~Window();

protected:
	HWND m_hwnd;
};

