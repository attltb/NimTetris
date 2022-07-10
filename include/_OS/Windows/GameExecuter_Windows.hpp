#ifndef _GameExecuter_WindowsHeader_
#define _GameExecuter_WindowsHeader_
#include "Game.hpp"
#include "Drawable.hpp"
#include "Timer.hpp"
#include "TimerManager.hpp"
#include "WindowMessageHandler.hpp"
#include <wtypes.h>
class GameExecuter_Windows {
	TimerManager& timerManager;
	Game* pGame;
	Timer* pFrameTimer;
	Bitmap32 display;
	BITMAPINFOHEADER displayInfo;
	std::pair<HWND, int> frameCallBackParam;
	int rssIconID;
	int rssIconSmallID;
	int rssCursurID;
	int rssAcceleratorID;

private:
	static void FrameCallback(void* params);

private:
	void initBufferBitmap(HWND hWnd);
	void updateBufferBitmap(HWND hWnd, Drawable screen);
	void displayBufferBitmap(HWND hWnd);
	void deleteBufferBitmap();

private:
	void onCreate(HWND hWnd, LPCREATESTRUCTA lpcrt);
	void onPaint(HWND hWnd);
	void onFrame(HWND hWnd, int frameNo);
	void onDestroy(HWND hWnd);

private:
	static KeyCode translateKeyCode(int winKeyCode);
	void onKeyDown(HWND hWnd, int winKeyCode);
	void onKeyUp(HWND hWnd, int winKeyCode);
	void onKeyInput(HWND hWnd, char ascii);

private:
	ATOM MyRegisterClass(Game& game, WNDPROC wndProc, HINSTANCE hInstance);
	BOOL InitInstance(Game& game, HINSTANCE hInstance, int nCmdShow);

public:
	LRESULT WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
	int wWinMain(Game& game, WNDPROC wndProc, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow);

public:
	GameExecuter_Windows(TimerManager& _timerManager, int _rssIconID, int _rssIconSmallID, int _rssCursurID, int _rssAcceleratorID) : timerManager(_timerManager),
		rssIconID(_rssIconID), rssIconSmallID(_rssIconSmallID), rssCursurID(_rssCursurID), rssAcceleratorID(_rssAcceleratorID) {}
};
#endif