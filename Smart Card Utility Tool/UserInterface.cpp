#include "UserInterface.h"
#include "Conection.h"


INT_PTR CALLBACK UI::CreateDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	

	switch (Message){

	case WM_INITDIALOG:{

		SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"blablabla");
		/*auto containerReaderi = Connect::ListCardReaders();
		for (const auto &it : containerReaderi){

			SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it.c_str());

		}*/
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)){
			case IDOK:{
				//aici ar fi bine sa pot retunrna un numar care reprezinta 
				//indexul cardului la care m-am conectat
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

LRESULT CALLBACK UI::MainWndProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HMENU hSysMenu;
	HWND hEdit = NULL;
	RECT dim;
	switch (Msg){

	case WM_CREATE: {
		hSysMenu = GetSystemMenu(hWnd, FALSE);
		RemoveMenu(hSysMenu, 2, MF_BYPOSITION);


		//consola
		GetClientRect(hWnd, &dim);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE | WS_EX_ACCEPTFILES, 
			"EDIT", "" , 
			WS_CHILD | WS_VISIBLE  | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_HSCROLL | WS_VSCROLL, //stiluri
			dim.left, dim.top, dim.right, dim.bottom, //dimensiuni initiale 
			hWnd, NULL, GetModuleHandle(NULL), NULL);
		//creeare font 
		HFONT hf;
		HDC hdc;
		long lfHeight;
		hdc = GetDC(NULL);
		lfHeight = -MulDiv(13, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		ReleaseDC(NULL, hdc);
		hf = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Times New Roman");
		//HGDIOBJ hfDefault = GetStockObject(DEFAULT_GUI_FONT);
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hf, TRUE);

		break;

	}
	case WM_SIZE: {
		GetClientRect(hWnd, &dim);
		MoveWindow(hEdit, dim.left, dim.top, abs(dim.right - dim.left), abs(dim.top - dim.bottom), TRUE);
	}
	//eventual un CASE: RETURN cand apasa pe enter sa se stearga ce a fost in consola se parseaza se proceseaza etc si poate sa scrie iar
	// si voila o consola home made :)


	case WM_COMMAND:
		switch (LOWORD(wParam)){
			case ID_MENU_SELECTCARD:{
					//Connect::EstablishContext();
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
		//aici va venii dezalocare context si alte dezalocari cred...
		//Connect::ClearContext();
		//Connect::Deconectare();
		//nu stiu ce sa deconectez aici pt ca alocarea se face in CreateDlgProc si nu stiu
		//ce card sa deconectez
		PostQuitMessage(WM_QUIT);
		return 0;
	}

	return DefWindowProc(hWnd, Msg, wParam, lParam);
}