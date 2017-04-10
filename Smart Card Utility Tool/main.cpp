#include"UserInterface.h"
#include"CMainWindow.h"

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	MSG   Msg;
	LPCTSTR ClsName = "Win32OOP";
	LPCTSTR WndName = "Java Card Utility Tool";

	CWApplication WinApp(hInstance, ClsName, UI::MainWndProc, 0);
	WinApp.Register();

	CWindow Wnd;
	Wnd.Create(hInstance, ClsName, WndName);

	Wnd.Show();

	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}
