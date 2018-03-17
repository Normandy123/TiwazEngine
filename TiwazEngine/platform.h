#pragma once

#define TIWAZ_APP __declspec(dllexport)

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Tiwaz
{
	TIWAZ_APP extern void InitPlatform(HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow);
}

namespace Tiwaz::Platform
{
	extern HINSTANCE hInstance;
	extern PWSTR pCmdLine;
	extern int nCmdShow;	
}
#endif