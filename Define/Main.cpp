#ifdef SFML_STATIC
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "jpeg.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "gdi32.lib")  
#endif // SFML_STATIC

#include "Game.h"

int main()
{
#ifdef _DEBUG
	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flag |= _CRTDBG_LEAK_CHECK_DF; // Turn on leak-checking bit
	_CrtSetDbgFlag(flag);
#endif
	//Game *g = new Game();
	//delete g;
	return 0;
}