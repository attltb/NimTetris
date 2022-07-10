#include "GameExecuter_Windows.hpp"
#include "WindowHandle_Windows.hpp"
#include <vector>
#include <windowsx.h>
HINSTANCE g_hInst; //
HWND hWndMain; //
void GameExecuter_Windows::initBufferBitmap(HWND hWnd) {
	HDC hdc = GetDC(hWnd);
	RECT crt;
	GetClientRect(hWnd, &crt);
	display.reset(crt.right, crt.bottom);
	displayInfo.biSize = 40;
	displayInfo.biWidth = display.width;
	displayInfo.biHeight = -display.height;
	displayInfo.biPlanes = 1;
	displayInfo.biBitCount = 32;
	displayInfo.biCompression = BI_RGB;
	displayInfo.biSizeImage = 32 * display.width * display.height;
	displayInfo.biXPelsPerMeter = 0;
	displayInfo.biYPelsPerMeter = 0;
	displayInfo.biClrUsed = 0;
	displayInfo.biClrImportant = 0;
	ReleaseDC(hWnd, hdc);
}
void GameExecuter_Windows::updateBufferBitmap(HWND hWnd, Drawable screen) {
	screen.drawOn(display, 0, 0);
	InvalidateRect(hWnd, NULL, FALSE);
	return;
}
void GameExecuter_Windows::displayBufferBitmap(HWND hWnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hWnd, &ps);
	SetDIBitsToDevice(hdc, 0, 0, display.width, display.height, 0, 0, 0, display.height, display.bits, (BITMAPINFO*)(&displayInfo), DIB_RGB_COLORS);
	EndPaint(hWnd, &ps);
	return;
}
void GameExecuter_Windows::deleteBufferBitmap() {
	display.free();
}

void GameExecuter_Windows::FrameCallback(void* params) {
	static int frameNo = 0;
	std::pair<HWND, int>* callBackParam = (std::pair<HWND, int>*)params;
	if (frameNo == callBackParam->second) {
		PostMessageA(callBackParam->first, WM_FRAME, callBackParam->second, 0);
		frameNo++;
	}
}
void GameExecuter_Windows::onCreate(HWND hWnd, LPCREATESTRUCTA lpcrt) {
	hWndMain = hWnd; //
	initBufferBitmap(hWnd);

	if (!pGame->initialize(WindowHandle_Windows::get(hWnd))) {
		PostQuitMessage(0);
		return;
	}
	if (!pGame->getWindowMessageHandler().onInitialize(WindowHandle_Windows::get(hWnd))) {
		PostQuitMessage(0);
		return;
	}

	frameCallBackParam = std::make_pair(hWnd, 0);
	timerManager.activateManager();
	pFrameTimer = timerManager.newTimer(FrameCallback, &frameCallBackParam, 0, 33);
}
void GameExecuter_Windows::onPaint(HWND hWnd) {
	displayBufferBitmap(hWnd);
}
void GameExecuter_Windows::onFrame(HWND hWnd, int frameNo) { 
	pGame->getWindowMessageHandler().onFrame(WindowHandle_Windows::get(hWnd), frameNo);
	updateBufferBitmap(hWnd, pGame->getWindowMessageHandler().onDraw());
	frameCallBackParam.second++;
}
void GameExecuter_Windows::onDestroy(HWND hWnd) {
	pFrameTimer->destroy();
	timerManager.terminateManager();

	pGame->getWindowMessageHandler().onFinalize(WindowHandle_Windows::get(hWnd));
	pGame->finalize(WindowHandle_Windows::get(hWnd));

	deleteBufferBitmap();
	PostQuitMessage(0);
	_CrtDumpMemoryLeaks();
}

KeyCode GameExecuter_Windows::translateKeyCode(int winKeyCode) {
	switch (winKeyCode) {
	case VK_ESCAPE: return KeyCode::ESC;
	case VK_F1: return KeyCode::F1;
	case VK_F2: return KeyCode::F2;
	case VK_F3: return KeyCode::F3;
	case VK_F4: return KeyCode::F4;
	case VK_F5: return KeyCode::F5;
	case VK_F6: return KeyCode::F6;
	case VK_F7: return KeyCode::F7;
	case VK_F8: return KeyCode::F8;
	case VK_F9: return KeyCode::F9;
	case VK_F10: return KeyCode::F10;
	case VK_F11: return KeyCode::F11;
	case VK_F12: return KeyCode::F12;
	case VK_SNAPSHOT: return KeyCode::PrtScr;
	case VK_SCROLL: return KeyCode::ScrollLock;
	case VK_PAUSE: return KeyCode::Pause;
	case VK_BACK: return KeyCode::Backspace;
	case VK_INSERT:	return KeyCode::Insert;
	case VK_HOME: return KeyCode::Home;
	case VK_PRIOR: return KeyCode::Pgup;
	case VK_END: return KeyCode::End;
	case VK_DELETE: return KeyCode::Delete;
	case VK_NEXT: return KeyCode::Pgdn;
	case VK_LEFT: return KeyCode::Left;
	case VK_RIGHT: return KeyCode::Right;
	case VK_UP: return KeyCode::Up;
	case VK_DOWN: return KeyCode::Down;
	case VK_NUMLOCK: return KeyCode::NumLock;
	case VK_NUMPAD0: return KeyCode::Num0;
	case VK_NUMPAD1: return KeyCode::Num1;
	case VK_NUMPAD2: return KeyCode::Num2;
	case VK_NUMPAD3: return KeyCode::Num3;
	case VK_NUMPAD4: return KeyCode::Num4;
	case VK_NUMPAD5: return KeyCode::Num5;
	case VK_NUMPAD6: return KeyCode::Num6;
	case VK_NUMPAD7: return KeyCode::Num7;
	case VK_NUMPAD8: return KeyCode::Num8;
	case VK_NUMPAD9: return KeyCode::Num9;
	case 0x30: return KeyCode::_0;
	case 0x31: return KeyCode::_1;
	case 0x32: return KeyCode::_2;
	case 0x33: return KeyCode::_3;
	case 0x34: return KeyCode::_4;
	case 0x35: return KeyCode::_5;
	case 0x36: return KeyCode::_6;
	case 0x37: return KeyCode::_7;
	case 0x38: return KeyCode::_8;
	case 0x39: return KeyCode::_9;
	case 0x41: return KeyCode::A;
	case 0x42: return KeyCode::B;
	case 0x43: return KeyCode::C;
	case 0x44: return KeyCode::D;
	case 0x45: return KeyCode::E;
	case 0x46: return KeyCode::F;
	case 0x47: return KeyCode::G;
	case 0x48: return KeyCode::H;
	case 0x49: return KeyCode::I;
	case 0x4A: return KeyCode::J;
	case 0x4B: return KeyCode::K;
	case 0x4C: return KeyCode::L;
	case 0x4D: return KeyCode::M;
	case 0x4E: return KeyCode::N;
	case 0x4F: return KeyCode::O;
	case 0x50: return KeyCode::P;
	case 0x51: return KeyCode::Q;
	case 0x52: return KeyCode::R;
	case 0x53: return KeyCode::S;
	case 0x54: return KeyCode::T;
	case 0x55: return KeyCode::U;
	case 0x56: return KeyCode::V;
	case 0x57: return KeyCode::W;
	case 0x58: return KeyCode::X;
	case 0x59: return KeyCode::Y;
	case 0x5A: return KeyCode::Z;
	case VK_TAB: return KeyCode::Tab;
	case VK_CAPITAL: return KeyCode::CapsLock;
	case VK_LSHIFT: return KeyCode::LShift;
	case VK_RSHIFT: return KeyCode::RShift;
	case VK_LCONTROL: return KeyCode::LCtrl;
	case VK_RCONTROL: return KeyCode::RCtrl;
	case VK_MENU: return KeyCode::Alt;
	case VK_SPACE: return KeyCode::Space;
	case VK_RETURN: return KeyCode::Enter;
	}
	return KeyCode::Charactor;
}
void GameExecuter_Windows::onKeyDown(HWND hWnd, int winKeyCode) {
	pGame->getWindowMessageHandler().onKeyDown(WindowHandle_Windows::get(hWnd), translateKeyCode(winKeyCode));
}
void GameExecuter_Windows::onKeyUp(HWND hWnd, int winKeyCode) {
	pGame->getWindowMessageHandler().onKeyUp(WindowHandle_Windows::get(hWnd), translateKeyCode(winKeyCode));
}
void GameExecuter_Windows::onKeyInput(HWND hWnd, char ascii) {
	pGame->getWindowMessageHandler().onKeyInput(WindowHandle_Windows::get(hWnd), ascii);
}

ATOM GameExecuter_Windows::MyRegisterClass(Game& game, WNDPROC wndProc, HINSTANCE hInstance) {
	WNDCLASSEXA wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, rssIconID ? MAKEINTRESOURCE(rssIconID) : IDI_APPLICATION);
	wcex.hCursor = LoadCursor(nullptr, rssCursurID ? MAKEINTRESOURCE(rssCursurID) : IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = game.getGameName();
	wcex.hIconSm = LoadIcon(wcex.hInstance, rssIconSmallID ? MAKEINTRESOURCE(rssIconSmallID) : IDI_APPLICATION);

	return RegisterClassExA(&wcex);
}
BOOL GameExecuter_Windows::InitInstance(Game& game, HINSTANCE hInstance, int nCmdShow) {
	RECT rect{ 20,20,20 + game.getInitialScreenWidth() ,20 + game.getInitialScreenHeight() };
	AdjustWindowRect(&rect, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0);

	HWND hWnd = CreateWindowA(game.getGameName(), game.getWindowTitle(), WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,
		CW_USEDEFAULT, 0, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, hInstance, nullptr);
	if (!hWnd) return FALSE;
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
LRESULT GameExecuter_Windows::WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_CREATE:
		onCreate(hWnd, (LPCREATESTRUCTA)lParam);
		break;
	case WM_PAINT:
		onPaint(hWnd);
		return 0;
	case WM_KEYDOWN:
		onKeyDown(hWnd, (int)wParam);
		break;
	case WM_KEYUP:
		onKeyUp(hWnd, (int)wParam);
		break;
	case WM_CHAR:
		onKeyInput(hWnd, (char)wParam);
		break;
	case WM_MOUSEMOVE:
		pGame->getWindowMessageHandler().onMouseMove(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDOWN:
		pGame->getWindowMessageHandler().onMouseLDown(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONUP:
		pGame->getWindowMessageHandler().onMouseLUp(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_LBUTTONDBLCLK:
		pGame->getWindowMessageHandler().onMouseLDouble(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_RBUTTONDOWN:
		pGame->getWindowMessageHandler().onMouseRDown(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_RBUTTONUP:
		pGame->getWindowMessageHandler().onMouseRUp(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_RBUTTONDBLCLK:
		pGame->getWindowMessageHandler().onMouseRDouble(WindowHandle_Windows::get(hWnd), GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
		break;
	case WM_DESTROY:
		onDestroy(hWnd);
		return 0;
	case WM_FRAME:
		onFrame(hWnd, (int)wParam);
		break;
	case WM_CUSTUM:
		pGame->getWindowMessageHandler().onCustom(WindowHandle_Windows::get(hWnd), (int)wParam, (void*)lParam);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
int GameExecuter_Windows::wWinMain(Game& game, WNDPROC wndProc, HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	g_hInst = hInstance;
	pGame = &game;
	MyRegisterClass(game, wndProc, hInstance);
	if (!InitInstance(game, hInstance, nCmdShow)) return FALSE;

	MSG msg;
	if (rssAcceleratorID) {
		HACCEL hAccelTable = LoadAcceleratorsA(hInstance, MAKEINTRESOURCE(rssAcceleratorID));
		while (GetMessageA(&msg, nullptr, 0, 0)) {
			if (!TranslateAcceleratorA(msg.hwnd, hAccelTable, &msg)) {
				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}
	}
	else {
		while (GetMessageA(&msg, nullptr, 0, 0)) {
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}
	return (int)msg.wParam;
}