#include "ApiInterface.h"
#include "Conection.h"
#include <Richedit.h>

WNDPROC editWndProc;
HWND hEdit;
DWORD contorLinie;


void AppendText(HWND hEditWnd, LPCTSTR Text)
{
	int idx = GetWindowTextLength(hEditWnd);
	SendMessage(hEditWnd, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
	SendMessage(hEditWnd, EM_REPLACESEL, 0, (LPARAM)Text);
}

LRESULT CALLBACK UI::SubclassEditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	
	/*CHARFORMAT _protectedText;
	ZeroMemory(&_protectedText, sizeof(_protectedText));
	_protectedText.cbSize = sizeof(_protectedText);
	_protectedText.dwMask = CFM_PROTECTED;
	_protectedText.dwEffects = CFE_PROTECTED;

	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(cf));
	cf.cbSize = sizeof(cf);
	cf.dwMask = CFM_BOLD;
	cf.dwEffects = CFE_BOLD;
	lstrcpy(cf.szFaceName, "Arial");
	*/
	SetFocus(hEdit);
	auto lineCount = 0;
	auto lineIndex = 0;
	auto lineLenght = 0; 
	switch (msg)
	{
		
	
	case WM_KEYDOWN:
		SendMessage(hEdit, EM_SETREADONLY, FALSE , 0);
		lineCount = SendMessage(hEdit, EM_GETLINECOUNT, 0, 0);
		lineIndex = SendMessage(hEdit, EM_LINEINDEX, lineCount - 1, 0);
		lineLenght = SendMessage(hEdit, EM_LINELENGTH, lineIndex, 0);
		if (lineLenght == 0)
		{
			AppendText(hEdit, ">>");
		}
		switch (wParam)
		{
		case VK_PRIOR:
			BlockInput(TRUE);
		case VK_NEXT:
			SetCaretPos(0, +1);
		case VK_BACK:
		{
			if (lineLenght == 2)
			{
				SendMessage(hEdit, EM_SETREADONLY, TRUE, NULL);
			}
		}
		case VK_RETURN:
		{
			/*
			SendMessage(hEdit, EM_SETSEL, lineIndex, lineIndex + lineLenght);
			
			SendMessage(hEdit, EM_SETCHARFORMAT, SCF_SELECTION | SCF_WORD, (LPARAM)&cf);
			SendMessage(hEdit, EM_SETEVENTMASK, 0, ENM_PROTECTED);*/
			char buffer[30];
			SendMessage(hEdit, EM_GETLINE, lineCount - 1, (LPARAM)buffer);

			buffer[lineLenght] = '\0';
			break;
		}
		}
	default:	
		return CallWindowProc(editWndProc, hwnd, msg, wParam, lParam);
	
	
	
	}
	return 0;
}

INT_PTR CALLBACK UI::CreateDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{


	switch (Message) {

	case WM_INITDIALOG: {

		//SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)"blablabla");
		auto containerReaderi = Connect::ListCardReaders();
		for (const auto &it : containerReaderi){

		SendMessage(GetDlgItem(hwnd, IDC_LIST1), LB_ADDSTRING, 0, (LPARAM)it.c_str());

		}
		return TRUE;
	}
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDOK: {
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
	OPENFILENAME ofn;
	char szFileName[MAX_PATH] = "";
	RECT dim;
	//DWORD contorLinie = 0;
	switch (Msg) {

	case WM_CREATE: {
		hSysMenu = GetSystemMenu(hWnd, FALSE);
		RemoveMenu(hSysMenu, 2, MF_BYPOSITION);


		GetClientRect(hWnd, &dim);
		hEdit = CreateWindowEx(WS_EX_CLIENTEDGE,
			"EDIT", "",
			WS_CHILD | WS_VISIBLE | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL | WS_HSCROLL | WS_VSCROLL, //stiluri
			dim.left, dim.top, dim.right, dim.bottom, //dimensiuni initiale 
			hWnd, NULL, GetModuleHandle(NULL), NULL);

		////fontul textului 
	/*	HFONT hf;
		HDC hdc;
		long lfHeight;
		hdc = GetDC(NULL);
		lfHeight = -MulDiv(13, GetDeviceCaps(hdc, LOGPIXELSY), 72);
		ReleaseDC(NULL, hdc);
		hf = CreateFont(lfHeight, 0, 0, 0, 0, TRUE, 0, 0, 0, 0, 0, 0, 0, "Bold");
		SendMessage(hEdit, WM_SETFONT, (WPARAM)hf, TRUE);*/

		editWndProc = (WNDPROC)SetWindowLongPtr(hEdit, GWLP_WNDPROC, (LONG_PTR)SubclassEditProc);

	}
					break;
	case WM_SIZE: {
		GetClientRect(hWnd, &dim);
		MoveWindow(hEdit, dim.left, dim.top, abs(dim.right - dim.left), abs(dim.top - dim.bottom), TRUE);
	}
				  break;
	
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_MENU_SELECTCARD: {
			Connect::EstablishContext();
			DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, CreateDlgProc);
		}
								 break;
		case ID_MENU_INSTALLAPPLET:
			
			

			ZeroMemory(&ofn, sizeof(ofn));

			ofn.lStructSize = sizeof(ofn); // SEE NOTE BELOW
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
			ofn.lpstrFile = szFileName;
			ofn.nMaxFile = MAX_PATH;
			ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
			ofn.lpstrDefExt = "txt";

			if (GetOpenFileName(&ofn))
			{
				// Do something usefull with the filename stored in szFileName 
			}
			//DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG1), hWnd, CreateDlgProc);

			break;
		case ID_MENU_KEYVAULT:

			break;
		}
		break;
	case WM_CTLCOLOREDIT:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkColor(hdcStatic, RGB(0, 0, 0));
		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
	}
	case WM_CTLCOLORSTATIC:
	{
		HDC hdcStatic = (HDC)wParam;
		SetTextColor(hdcStatic, RGB(255, 255, 255));
		SetBkColor(hdcStatic, RGB(0, 0, 0));
		return (INT_PTR)CreateSolidBrush(RGB(0, 0, 0));
	}
	case WM_DESTROY:
		//aici va venii dezalocare context si alte dezalocari cred...
		//Connect::ClearContext();
		//Connect::Deconectare();
		//nu stiu ce sa deconectez aici pt ca alocarea se face in CreateDlgProc si nu stiu
		//ce card sa deconectez
		PostQuitMessage(WM_QUIT);
		return 0;
	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}