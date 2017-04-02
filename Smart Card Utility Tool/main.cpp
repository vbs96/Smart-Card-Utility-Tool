
#include <windows.h>
#include<WinUser.h>
#include "CWinApp.h"
#include "CMainWindow.h"
#include"resource.h"

//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = L"Win32OOP";
	LPCTSTR WndName = L"Java Card Utility Tool";
	//LPCTSTR Wnd2Name = L"Choose Card";

	// Initialize the application class
	CWApplication WinApp(hInstance, ClsName, MainWndProc,0);
	WinApp.Register();

	// Create the main window
	CWindow Wnd;
	Wnd.Create(hInstance, ClsName, WndName);

	
	// Display the main winow
	Wnd.Show();

	// Process the main window's messages
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
//---------------------------------------------------------------------------
INT_PTR CALLBACK CreateDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
		}
		break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
	default:
		return FALSE;
	}
}
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HMENU hSysMenu;
	HWND hListBox, hDlg;
	switch (Msg)
	{
	case WM_CREATE:
		hSysMenu = GetSystemMenu(hWnd, FALSE);
		RemoveMenu(hSysMenu, 2, MF_BYPOSITION);
		

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_SELECTCARD:
		{
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, CreateDlgProc);

	
		}
			break;
		case ID_MENU_INSTALLAPPLET:

			break;
		case ID_MENU_KEYVAULT:

			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		return 0;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}


//-----------------------------------------------------------------------
