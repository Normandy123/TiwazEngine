#include <engine.h>

#define DEBUGMODE 1

#if DEBUGMODE
int main(int argc, char* argv[])
{
	Tiwaz::RunEngine(true, false);

	const int result = Tiwaz::ExitEngine();

	return result;
}
#endif

#if !DEBUGMODE

#ifdef _WIN64
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Tiwaz::RunEngine(false, false);

	const int result = Tiwaz::ExitEngine();

	return result;
}
#endif

#endif