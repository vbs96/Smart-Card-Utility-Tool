#include "CWinApp.h"
#include"resource.h"

//---------------------------------------------------------------------------
CWApplication::CWApplication(HINSTANCE hInst, LPCTSTR ClsName,
	WNDPROC WndPrc, LPCTSTR MenuName)
{
	// Initializing the application using the application member variable
	_WndClsEx.cbSize = sizeof(WNDCLASSEX);
	_WndClsEx.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_WndClsEx.lpfnWndProc = WndPrc;
	_WndClsEx.cbClsExtra = 0;
	_WndClsEx.cbWndExtra = 0;
	_WndClsEx.hInstance = hInst;
	_WndClsEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	_WndClsEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	_WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_WndClsEx.lpszMenuName = MenuName;
	_WndClsEx.lpszClassName = ClsName;
	_WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	_WndClsEx.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
}
//---------------------------------------------------------------------------
void CWApplication::Register()
{
	RegisterClassEx(&_WndClsEx);
}
//---------------------------------------------------------------------------