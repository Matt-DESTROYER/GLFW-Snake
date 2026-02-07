#include "game.h"

// Windows GUI entry point wrapper
#if defined(_WIN32) && defined(NDEBUG)
#include <windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	(void)hInstance;
	(void)hPrevInstance;
	(void)lpCmdLine;
	(void)nCmdShow;
	return init_game();
}
#else
// Standard console entry point for all other platforms and Debug builds
int main() {
	return init_game();
}
#endif
