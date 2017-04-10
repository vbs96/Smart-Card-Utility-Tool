#pragma once
#include "CWinApp.h"
#include "resource.h"

namespace UI {
	LRESULT CALLBACK SubclassEditProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);
	INT_PTR CALLBACK CreateDlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
}