#ifndef WINCTRLS_H
#define WINCTRLS_H

#include <windows.h>

//---------------------------------------------------------------------------
class CWControl
{
public:
	CWControl();
	virtual ~CWControl();

	HWND Create(HINSTANCE hinst, LPCTSTR clsname,
		LPCTSTR wndname, HWND parent = NULL,
		DWORD dStyle = WS_OVERLAPPEDWINDOW,
		int x = CW_USEDEFAULT, int y = CW_USEDEFAULT,
		int width = 450, int height = 380);
	BOOL Show(int dCmdShow = SW_SHOWNORMAL);
	operator HWND();
protected:
	HWND hwnd;
	HINSTANCE mhInst;

public:
	HINSTANCE GetInstance();

private:
};
//---------------------------------------------------------------------------

#endif	// WINCTRLS_H
