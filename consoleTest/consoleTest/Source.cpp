#include <windows.h>
#include <iostream>
#include <fstream>
#include <conio.h>
#include <stdio.h>
#include <crtdbg.h>
#include<fcntl.h>
#include<io.h>
void RedirectIOToConsole()
{

	int hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;
	
	AllocConsole();
	
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);

	coninfo.dwSize.Y = 500;
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

	lStdHandle = (long)GetStdHandle(STD_OUTPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stdout = *fp;
	setvbuf(stdout, NULL, _IONBF, 0);

	lStdHandle = (long)GetStdHandle(STD_INPUT_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "r");
	*stdin = *fp;
	setvbuf(stdin, NULL, _IONBF, 0);

	lStdHandle = (long)GetStdHandle(STD_ERROR_HANDLE);
	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
	fp = _fdopen(hConHandle, "w");
	*stderr = *fp;
	setvbuf(stderr, NULL, _IONBF, 0);

	std::ios::sync_with_stdio();
}


int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	RedirectIOToConsole();
	int iVar;

	fprintf(stdout, "Test output to stdout\n");
	fprintf(stderr, "Test output to stderr\n");
	fprintf(stdout, "Enter an integer to test stdin: ");

	std::cin >> iVar;

	printf("You entered %d\n", iVar);

	//test iostreams

	std::cout << "Test output to cout" << std::endl;

	std::cerr << "Test output to cerr" << std::endl;

	std::clog << "Test output to clog" << std::endl;

	std::cout << "Enter an integer to test cin: ";

	std::cin >> iVar;

	std::cout << "You entered " << iVar << std::endl;





	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);

	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);

	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);

	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);

	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);

	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDERR);

	_RPT0(_CRT_WARN, "This is testing _CRT_WARN output\n");

	_RPT0(_CRT_ERROR, "This is testing _CRT_ERROR output\n");

	_ASSERT(0 && "testing _ASSERT");

	_ASSERTE(0 && "testing _ASSERTE");

	Sleep(5000);

	return 0;

}

