#pragma once
#include <windows.h>

//---------------------------------------------------------------------------
class CWApplication
{
public:
	// This constructor will initialize the application
	CWApplication(HINSTANCE hInst, LPCTSTR ClasName, WNDPROC WndPrc, LPCTSTR MenuName = NULL);

	void Register();

protected:
	// Global variable that holds the application
	WNDCLASSEX _WndClsEx;
};
//---------------------------------------------------------------------------
