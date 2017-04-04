#pragma once
#include "CWinApp.h"
#include "CMainWindow.h"
#include "resource.h"

namespace UI {
	LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK CreateDlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
}