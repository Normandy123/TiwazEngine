#include <engine.h>

#define CONSOLEMODE 1
#define EDITORMODE 0

#if CONSOLEMODE
int main(int argc, char* argv[])
{
	Tiwaz::RunEngine(true, false);

	const int result = Tiwaz::ExitEngine();

	return result;
}
#endif

#if !CONSOLEMODE

#include <platform.h>

#ifdef _WIN64
 
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	Tiwaz::InitPlatform(hInstance, pCmdLine, nCmdShow);

	Tiwaz::RunEngine(false, false);

	const int result = Tiwaz::ExitEngine();

	return result;
}
#endif

#endif