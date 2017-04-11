#include"ApiInterface.h"
#include"Conection.h"

LRESULT CALLBACK UI::DlgProc(HWND hWndDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_INITDIALOG:
	{
		auto container = Connect::ListCardReaders();
		//SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"blablabla");
			for (const auto &it : container)
		{
		  SendMessage(GetDlgItem(hWndDlg, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it.c_str());
		}
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
		}
		break;
		case IDCANCEL:
			EndDialog(hWndDlg, IDCANCEL);
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
		Connect::EstablishContext();

		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_MENU_SELECTCARD:
		{

			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, UI::DlgProc);




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
