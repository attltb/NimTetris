#ifndef _NimTMessageReactorHeader_
#define _NimTMessageReactorHeader_
#include "WindowMessageHandler.hpp"
#include "NimTetrisGraphics.hpp"
#include "NimTBackground.hpp"
#include "NimTBoard.hpp"
class NimTetris;
class NimTMessageHandler : public WindowMessageHandler {
	ThreadManager& threadManager;
	ResourceCollection& resources;
	NimTetrisAutosaveds& autosaveds;
	NimTetrisGraphics* pGraphics;
	NimTBackground* pBackground;
	NimTBoard* pBoard;

public:
	bool onInitialize(WindowHandle wnd);
	bool onFinalize(WindowHandle wnd);
	void onFrame(WindowHandle wnd, int frameNo);
	void onKeyDown(WindowHandle wnd, KeyCode keycode);
	void onKeyUp(WindowHandle wnd, KeyCode keycode);
	void onKeyInput(WindowHandle wnd, char charactor);
	void onMouseMove(WindowHandle wnd, int xPos, int yPos);
	void onMouseLDown(WindowHandle wnd, int xPos, int yPos);
	void onMouseLUp(WindowHandle wnd, int xPos, int yPos);
	void onMouseLDouble(WindowHandle wnd, int xPos, int yPos);
	void onMouseRDown(WindowHandle wnd, int xPos, int yPos);
	void onMouseRUp(WindowHandle wnd, int xPos, int yPos);
	void onMouseRDouble(WindowHandle wnd, int xPos, int yPos);
	void onCustom(WindowHandle wnd, int kind, void* params);

public:
	Drawable onDraw() const;

public:
	NimTMessageHandler(ThreadManager& _threadManager, ResourceCollection& _resources, NimTetrisAutosaveds& _autosaveds) :
		threadManager(_threadManager), resources(_resources), autosaveds(_autosaveds) {};
};
#endif