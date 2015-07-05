#pragma once
class FGameUI;
#include "FGame.h"
#include "FScene.h"
#include "IntroScene.h"

class FGameUI
{
public:
	#pragma message("in fgameui")
	FGameUI(FGame *game, char* className, char* title, int width, int height, int x, int y, int bits, bool fullscreenflag);
	~FGameUI(void);

	bool KillWindow(void);
	bool Show();

	HWND GetHWND(){return mHWND;}
	HDC GetHDC(){return mHDC;}
	bool GetActive(){return uiActive;}
	void SetActive(bool active){uiActive = active;}
	bool SetFullScreen(bool fullscreenflag);
	bool GetFullScreen(){return fullscreen;}
	FGame *GetGame(){return game;}
	int GetWidth(){return width;}
	int GetHeight(){return height;}

	void Update();
	bool DrawScene();
	void SpecificDraw();

	void SetScene(FScene *newscene);

	void ReSizeGLScene(int width, int height);

	LRESULT CALLBACK FGameWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	//static FGameUI* globalUI;
protected:
	bool InitGL(bool reset = false);
	HDC mHDC;
	HGLRC mHRC;
	HWND mHWND;
	HINSTANCE mHINSTANCE;

	FGame* game;

	FScene *scene;

	bool uiActive;
	bool shown;
	bool fullscreen;

	char* className;
	char* title;
	int width;
	int height;
	int x;
	int y;
	int bits;

	bool glinitialized;

	WNDPROC WndProc;
};
