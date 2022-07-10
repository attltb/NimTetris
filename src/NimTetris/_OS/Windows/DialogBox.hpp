#ifndef _DialogBoxHeader_
#define _DialogBoxHeader_
#include <Windows.h>
INT_PTR CALLBACK SelectPlayerProc(HWND hSPP,UINT iMessage,WPARAM wParam,LPARAM lParam);
INT_PTR CALLBACK EditPlayersProc(HWND hEPSP,UINT iMessage,WPARAM wParam,LPARAM lParam);
INT_PTR CALLBACK EditPlayerProc(HWND hEPSP,UINT iMessage,WPARAM wParam,LPARAM lParam);
INT_PTR CALLBACK DeleteConfirm(HWND hEPSP,UINT iMessage,WPARAM wParam,LPARAM lParam);
#endif