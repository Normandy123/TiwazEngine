#include "platform.h"

#ifdef _WIN64

namespace Tiwaz
{
	void InitPlatform(HINSTANCE hInstance, PWSTR pCmdLine, int nCmdShow)
	{
		Platform::hInstance = hInstance;
		Platform::pCmdLine = pCmdLine;
		Platform::nCmdShow = nCmdShow;
	}
}

namespace Tiwaz::Platform
{
	HINSTANCE hInstance;
	PWSTR pCmdLine;
	int nCmdShow;
}
#endif