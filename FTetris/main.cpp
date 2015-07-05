#include <windows.h>
#include "FTetris.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd){
	srand(time(0));
	FTetris *prog = new FTetris();
	return (prog->Start("3D Tetris By Floris Kint"));
}