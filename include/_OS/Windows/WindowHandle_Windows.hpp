#ifndef _WindowHandle_WindowsHeader_
#define _WindowHandle_WindowsHeader_
#include "WindowHandle.hpp"
#include <wtypes.h>
#define WM_FRAME (WM_USER+1)
#define WM_CUSTUM (WM_USER+2)
class WindowHandle_Windows : public WindowHandle_ {
public:
	HWND hWnd;

public:
	static WindowHandle get(HWND hWnd) {
		return WindowHandle(std::shared_ptr<WindowHandle_>(new WindowHandle_Windows(hWnd)));
	}

public:
	void msgCustom(int kind, void* params) {
		PostMessageA(hWnd, WM_CUSTUM, kind, (LPARAM)params);
	}
	void msgError(std::string msgText) {
		MessageBoxA(hWnd, msgText.c_str(), "Error", MB_OK);
	}
	void exit() {
		PostMessageA(hWnd, WM_DESTROY, 0, 0);
	}

public:
	WindowHandle_Windows(HWND _hWnd) : hWnd(_hWnd) {};
};
#endif