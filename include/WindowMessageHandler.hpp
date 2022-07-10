#ifndef _WinMessageReactorHeader_
#define _WinMessageReactorHeader_
#include "KeyCode.hpp"
#include "Drawable.hpp"
#include "WindowHandle.hpp"
class WindowMessageHandler {
public:
	virtual bool onInitialize(WindowHandle wnd) {
		return true;
	};
	virtual bool onFinalize(WindowHandle wnd) {
		return true;
	};
	virtual void onFrame(WindowHandle wnd, int frameNo) {};
	virtual void onKeyDown(WindowHandle wnd, KeyCode keycode) {};
	virtual void onKeyUp(WindowHandle wnd, KeyCode keycode) {};
	virtual void onKeyInput(WindowHandle wnd, char charactor) {};
	virtual void onMouseMove(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseLDown(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseLUp(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseLDouble(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseRDown(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseRUp(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onMouseRDouble(WindowHandle wnd, int xPos, int yPos) {};
	virtual void onCustom(WindowHandle wnd, int kind, void* params) {};

public:
	virtual Drawable onDraw() const = 0;

public:
	virtual ~WindowMessageHandler() {};
};
#endif