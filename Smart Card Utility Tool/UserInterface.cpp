#include"UserInterface.h"

LRESULT CALLBACK UI::DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
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

LRESULT CALLBACK UI::MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
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