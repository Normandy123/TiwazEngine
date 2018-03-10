#include "platform.h"

#ifdef _WIN64
namespace Tiwaz::Platform
{
	HINSTANCE h_instance = GetModuleHandle(0);
}
#endif