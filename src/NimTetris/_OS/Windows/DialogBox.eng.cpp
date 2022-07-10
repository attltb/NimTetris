#include "resource.h"
#include "DialogBox.hpp"
#include "NimTetrisAutosaveds.hpp"
#include <Windowsx.h>
using namespace std;
extern HINSTANCE g_hInst;
INT_PTR CALLBACK SelectPlayerProc(HWND hSPP, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
	{
		SetWindowLongPtrA(hSPP, GWLP_USERDATA, lParam);
		RECT R1, R2;
		GetWindowRect(GetWindow(hSPP, GW_OWNER), &R1); GetWindowRect(hSPP, &R2);
		int Sx = R2.right - R2.left;
		int Px = R1.left + (R1.right - R1.left) / 2 - Sx / 2;
		int Sy = R2.bottom - R2.top;
		int Py = R1.top + (R1.bottom - R1.top) / 2 - Sy / 2;
		MoveWindow(hSPP, Px, Py, Sx, Sy, 1);

		pair<NimTetrisAutosaveds*, int>* val = (pair<NimTetrisAutosaveds*, int>*)lParam;
		NimTetrisAutosaveds& autosaveds = *val->first;
		int targetPlayer = val->second;

		if (targetPlayer == 1) SetWindowTextA(hSPP, "Player1 setting");
		else SetWindowTextA(hSPP, "Player2 setting");

		for (auto it = NimTetrisAutosaveds::standardPlayers.begin(); it != NimTetrisAutosaveds::standardPlayers.end(); it++) {
			SendMessageA(GetDlgItem(hSPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)it->name);
		}
		for (auto it = autosaveds.custumPlayers.begin(); it != autosaveds.custumPlayers.end(); it++) {
			SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)it->name);
		}

		NimTetrisPlayerInfo& targetPlayerInfo = (targetPlayer == 1) ? autosaveds.lastPlayer1Info : autosaveds.lastPlayer2Info;
		if (!targetPlayerInfo.isCustum()) {
			CheckRadioButton(hSPP, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
			SendMessageA(GetDlgItem(hSPP, IDC_COMBO1), CB_SETCURSEL, autosaveds.findStandardPlayerPos(targetPlayerInfo.control), 0);
			ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO2), 0);
			if (!autosaveds.custumPlayers.empty()) SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_SETCURSEL, 0, 0);
		}
		else {
			CheckRadioButton(hSPP, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
			SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_SETCURSEL, autosaveds.findCustumPlayerPos(targetPlayerInfo.getCustumPlayerID()), 0);
			ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO1), 0);
			SendMessageA(GetDlgItem(hSPP, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		}
		return TRUE;
	}
	case WM_COMMAND:
	{
		pair<NimTetrisAutosaveds*, int>* val = (pair<NimTetrisAutosaveds*, int>*)GetWindowLongPtr(hSPP, GWLP_USERDATA);
		NimTetrisAutosaveds& autosaveds = *val->first;
		int targetPlayer = val->second;
		NimTetrisPlayerInfo& targetPlayerInfo = (targetPlayer == 1) ? autosaveds.lastPlayer1Info : autosaveds.lastPlayer2Info;
		switch (LOWORD(wParam)) {
		case IDC_RADIO1:
			if (IsDlgButtonChecked(hSPP, IDC_RADIO1) == BST_CHECKED) {
				ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO1), 1);
				ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO2), 0);
			}
			break;
		case IDC_RADIO2:
			if (IsDlgButtonChecked(hSPP, IDC_RADIO2) == BST_CHECKED) {
				ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO2), 1);
				ComboBox_Enable(GetDlgItem(hSPP, IDC_COMBO1), 0);
			}
			break;
		case IDC_BUTTON1:
		{
			vector<NimTetrisPlayerInfo> oldcustumPlayers = autosaveds.custumPlayers;
			if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG2), hSPP, EditPlayersProc, (LPARAM)&autosaveds) == IDOK) {
				SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_RESETCONTENT, 0, 0);
				for (auto it = autosaveds.custumPlayers.begin(); it != autosaveds.custumPlayers.end(); it++) {
					SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_ADDSTRING, 0, (LPARAM)it->name);
				}
				if (!autosaveds.custumPlayers.empty()) SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_SETCURSEL, 0, 0);
			}
			else autosaveds.custumPlayers = oldcustumPlayers;
			break;
		}
		case IDOK:
			if (IsDlgButtonChecked(hSPP, IDC_RADIO1) == BST_CHECKED) {
				if (SendMessageA(GetDlgItem(hSPP, IDC_COMBO1), CB_GETCURSEL, 0, 0) == LB_ERR) {
					MessageBoxA(hSPP, "No item is selected.", "ERROR", MB_OK);
					break;
				}
				size_t pos = SendMessageA(GetDlgItem(hSPP, IDC_COMBO1), CB_GETCURSEL, 0, 0);
				targetPlayerInfo = NimTetrisAutosaveds::standardPlayers[pos];
			}
			else {
				if (SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_GETCURSEL, 0, 0) == LB_ERR) {
					MessageBoxA(hSPP, "No item is selected.", "ERROR", MB_OK);
					break;
				}
				size_t pos = SendMessageA(GetDlgItem(hSPP, IDC_COMBO2), CB_GETCURSEL, 0, 0);
				targetPlayerInfo = autosaveds.custumPlayers[pos];
			}
			EndDialog(hSPP, IDOK);
			return TRUE;
		}
		break;
	}
	}
	return FALSE;
}
INT_PTR CALLBACK EditPlayersProc(HWND hEPSP, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
	{
		SetWindowLongPtrA(hEPSP, GWLP_USERDATA, lParam);
		NimTetrisAutosaveds& autosaveds = *((NimTetrisAutosaveds*)lParam);
		for (auto it = autosaveds.custumPlayers.begin(); it != autosaveds.custumPlayers.end(); it++) {
			SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it->name);
		}
		return TRUE;
	}
	case WM_COMMAND:
	{
		NimTetrisAutosaveds& autosaveds = *((NimTetrisAutosaveds*)GetWindowLongPtr(hEPSP, GWLP_USERDATA));
		switch (LOWORD(wParam)) {
		case IDC_BUTTON1:
		{
			NimTetrisPlayerInfo newPlayerInfo(0);
			if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hEPSP, EditPlayerProc, (LPARAM)&newPlayerInfo) == IDOK) {
				autosaveds.addCustumPlayer(newPlayerInfo);
				SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)newPlayerInfo.name);
			}
		}
			break;
		case IDC_BUTTON2:
		{
			size_t pos = SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_GETCURSEL, 0, 0);
			if (pos == LB_ERR) {
				MessageBoxA(hEPSP, "No item is selected.", "ERROR", MB_OK);
				break;
			}
			NimTetrisPlayerInfo newPlayerInfo(autosaveds.custumPlayers[pos]);
			if (DialogBoxParam(g_hInst, MAKEINTRESOURCE(IDD_DIALOG3), hEPSP, EditPlayerProc, (LPARAM)&newPlayerInfo) == IDOK) {
				autosaveds.custumPlayers[pos] = newPlayerInfo;
				SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_RESETCONTENT, 0, 0);
				for (auto it = autosaveds.custumPlayers.begin(); it != autosaveds.custumPlayers.end(); it++) {
					SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it->name);
				}
			}
			break;
		}
		case IDC_BUTTON3:
		{
			size_t pos = SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_GETCURSEL, 0, 0);
			if (SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_GETCURSEL, 0, 0) == LB_ERR) {
				MessageBoxA(hEPSP, "No item is selected.", "ERROR", MB_OK);
				break;
			}
			if (DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG4), hEPSP, DeleteConfirm) == IDOK) {
				autosaveds.removeCustumPlayerAt(pos);
				SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_RESETCONTENT, 0, 0);
				for (auto it = autosaveds.custumPlayers.begin(); it != autosaveds.custumPlayers.end(); it++) {
					SendMessageA(GetDlgItem(hEPSP, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it->name);
				}
			}
			break;
		}
		case IDOK:
			EndDialog(hEPSP, IDOK);
			return TRUE;
		case IDCANCEL:
			EndDialog(hEPSP, IDCANCEL);
			return FALSE;
		}
	}
	}
	return FALSE;
}
INT_PTR CALLBACK EditPlayerProc(HWND hEPP, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_INITDIALOG:
	{
		SetWindowLongPtrA(hEPP, GWLP_USERDATA, lParam);
		NimTetrisPlayerInfo& newPlayerInfo = *((NimTetrisPlayerInfo*)lParam);

		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_0");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_1");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_2");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_3");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_4");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_5");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_6");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_7");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_8");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_9");
		SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_ADDSTRING, 0, (LPARAM)"AI_10");
		SetDlgItemInt(hEPP, IDC_EDIT1, newPlayerInfo.ELO, 1);
		SetDlgItemTextA(hEPP, IDC_EDIT2, newPlayerInfo.name);

		if (newPlayerInfo.control == NimTetrisPlayerInfo::CONTROL::USER) {
			SendMessageA(GetDlgItem(hEPP, IDC_CHECK1), BM_SETCHECK, BST_CHECKED, 0);
			ComboBox_Enable(GetDlgItem(hEPP, IDC_COMBO1), 1);
			SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_SETCURSEL, 0, 0);
		}
		else {
			SendMessageA(GetDlgItem(hEPP, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
			ComboBox_Enable(GetDlgItem(hEPP, IDC_COMBO1), 0);
			SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_SETCURSEL, (int)newPlayerInfo.control - 1, 0);
		}

		EnableWindow(GetDlgItem(hEPP, IDC_EDIT1), 0);
		if (!newPlayerInfo.getCustumPlayerID()) {
			EnableWindow(GetDlgItem(hEPP, IDC_CHECK1), 1);
			SendMessageA(GetDlgItem(hEPP, IDC_CHECK1), BM_SETCHECK, BST_UNCHECKED, 0);
			ComboBox_Enable(GetDlgItem(hEPP, IDC_COMBO1), 0);
		}
		return TRUE;
	}
	case WM_COMMAND:
	{
		NimTetrisPlayerInfo& newPlayerInfo = *((NimTetrisPlayerInfo*)GetWindowLongPtr(hEPP, GWLP_USERDATA));
		switch (LOWORD(wParam)) {
		case IDC_CHECK1:
			if (SendMessageA(GetDlgItem(hEPP, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED) ComboBox_Enable(GetDlgItem(hEPP, IDC_COMBO1), 1);
			else ComboBox_Enable(GetDlgItem(hEPP, IDC_COMBO1), 0);
			break;
		case IDC_CHECK2:
			break;
		case IDOK:
		{
			int nameLength = GetDlgItemTextA(hEPP, IDC_EDIT2, newPlayerInfo.name, 16);
			if (nameLength > 16) {
				MessageBoxA(hEPP, "Names with more than 16 characters cannot be used.", "ERROR", MB_OK);
				break;
			}
			else if (nameLength < 1) {
				MessageBoxA(hEPP, "Player name is not inserted.", "ERROR", MB_OK);
				break;
			}

			if (SendMessageA(GetDlgItem(hEPP, IDC_CHECK1), BM_GETCHECK, 0, 0) == BST_CHECKED) {
				newPlayerInfo.control = (NimTetrisPlayerInfo::CONTROL)SendMessageA(GetDlgItem(hEPP, IDC_COMBO1), CB_GETCURSEL, 0, 0);
			}
			else newPlayerInfo.control = NimTetrisPlayerInfo::CONTROL::USER;
			EndDialog(hEPP, IDOK);
			return TRUE;
		}
		case IDCANCEL:
			EndDialog(hEPP, IDCANCEL);
			return FALSE;
		}
		break;
	}
	}
	return FALSE;
}
INT_PTR CALLBACK DeleteConfirm(HWND hEPSP, UINT iMessage, WPARAM wParam, LPARAM lParam) {
	switch (iMessage) {
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK:
			EndDialog(hEPSP, IDOK);
			return TRUE;
			break;
		case IDCANCEL:
			EndDialog(hEPSP, IDCANCEL);
			return FALSE;
		}
	}
	return FALSE;
}