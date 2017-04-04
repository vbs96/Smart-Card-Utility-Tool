#include"CWControl.h"

//---------------------------------------------------------------------------
CWControl::CWControl()
	: hwnd(0)
{
}
//---------------------------------------------------------------------------
CWControl::~CWControl()
{
}
//---------------------------------------------------------------------------
CWControl::operator HWND()
{
	return hwnd;
}
//---------------------------------------------------------------------------
HWND CWControl::Create(HINSTANCE hinst, LPCTSTR clsname,
	LPCTSTR wndname, HWND parent,
	DWORD dStyle,
	int x, int y,
	int width, int height)
{
	hwnd = CreateWindow(clsname, wndname, dStyle,
		x, y, width, height, parent, NULL, hinst, NULL);

	return hwnd;
}
//---------------------------------------------------------------------------
BOOL CWControl::Show(int dCmdShow)
{
	BOOL CanShow = ::ShowWindow(hwnd, dCmdShow);

	if (CanShow)
		return TRUE;
	return FALSE;
}
//---------------------------------------------------------------------------
HINSTANCE CWControl::GetInstance()
{
	return mhInst;
}
//---------------------------------------------------------------------------