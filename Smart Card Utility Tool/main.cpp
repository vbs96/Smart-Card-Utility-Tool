
#include <windows.h>
#include "CWinApp.h"
#include "CMainWindow.h"
#include"resource.h"
#include"Conection.h"

//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
//---------------------------------------------------------------------------
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = "Win32OOP";
	LPCTSTR WndName = "Java Card Utility Tool";
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


