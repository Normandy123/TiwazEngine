#pragma once

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Tiwaz::Platform
{
	extern HINSTANCE h_instance;
}

#endif