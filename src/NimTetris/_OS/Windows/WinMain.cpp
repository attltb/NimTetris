#include "resource.h"
#include "TimerManager_Windows.hpp"
#include "ThreadManager_Windows.hpp"
#include "GameExecuter_Windows.hpp"
#include "NimTetris.hpp"
#include <windows.h>
ThreadManager_Windows threadManager_Windows;
TimerManager_Windows timerManager_Windows;
GameExecuter_Windows engine(timerManager_Windows, IDI_GAMETW, IDI_SMALL, 0, IDR_ACCELERATOR);
NimTetris nimTetris(threadManager_Windows, timerManager_Windows);

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	return engine.WndProc(hWnd, iMessage, wParam, lParam);
}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	return engine.wWinMain(nimTetris, WndProc, hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}