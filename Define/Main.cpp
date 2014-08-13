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
	Game *g = new Game();
	delete g;
	return 0;
}