
#include <windows.h>
#include "CWinApp.h"
#include "CMainWindow.h"
#include"resource.h"

//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = "Win32OOP";
	LPCTSTR WndName = "Java Card Utility Tool";
	//LPCTSTR Wnd2Name = L"Choose Card";

	// Initialize the application class
	CWApplication WinApp(hInstance, ClsName,MessageProcedure,0);
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
LRESULT CALLBACK DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
		return TRUE;

	case WM_COMMAND:
		switch (wParam)
		{
		case IDOK:
			EndDialog(hWndDlg, 0);
			return TRUE;
		}
		break;
	}

	return FALSE;
}

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam)
{
	HMENU hSysMenu;
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
			MessageBox(hWnd, "fml", "FML", 0);
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
